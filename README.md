# lsensors
### lm_sensors interface and logger written in C and Python

## Install
Clone the repository of the project. And move inside it:
```bash
$ git clone https://github.com/H1alus/lsensors.git
$ cd lsensors
``` 
make sure you have make, gcc and python3 installed.  
Download the lm_sensors-devel ad lm_sensors packages: 

<b>Fedora or any RHEL based distro:</b>  
```bash
$ sudo dnf install lm_sensors-devel lm_sensors
```

<b>Debian/Ubuntu based distro:</b>
```bash
$ sudo apt install lm_sensors-devel lm_sensors
```  

<b> Arch based distro:</b>  
```bash
$ sudo pacman -S lm_sensors
```  

Now do in the root dir of the project:
```bash
$ make
```

Make sure "lsensors" file has exec permission:
```bash
$ sudo chmod +x lsensors
```
Run this to let lsensors configure the settings.json file: 
```bash
$ ./lsensors
```
If you wish add the program to PATH.  
For example copy the project directory in /opt and add to your .bashrc:
```bash
export PATH=$PATH:/opt/lsensors
```

## Configure and Run
lsensors by default runs as logger to a file
created in your working dir as "thermals.log".  
Note that you need to first set the "settings.json" in the "etc" folder of the project as you like. Set to "true" the sensors you want to log; usually the names are enough explicit  by their own.

Other arguments are:  
Show help message:
```bash
$ lsensors --help
```
Print to stdout:
```bash
$ lsensors -p
```
Generate settings.json file:
```bash
$ lsensors -i
```
## LICENSE
This code is distributed under the GNU General Public License V3, for further more information, check the LICENSE file.

## Notes
You can run lsensors as a daemon.  
This was made by myself in a short period of time. There's some stuff I'd like to change in the future but for the mean time it's working with no much cpu or memory usage and that's what matters for me.

## TO DO
* Recognize measurement unit for each type of subfeature