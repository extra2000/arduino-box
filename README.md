# arduino-box

| License | Versioning | Build |
| ------- | ---------- | ----- |
| [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT) | [![semantic-release](https://img.shields.io/badge/%20%20%F0%9F%93%A6%F0%9F%9A%80-semantic--release-e10079.svg)](https://github.com/semantic-release/semantic-release) | [![Build status](https://ci.appveyor.com/api/projects/status/auodk36lsf1py3ir/branch/master?svg=true)](https://ci.appveyor.com/project/nikAizuddin/arduino-box/branch/master) |

Developer box for [Arduino](https://www.arduino.cc).


## Creating Vagrant Box

Copy example pillar file for Arduino. Optionally you may want to edit the values in the `arduino.sls`:
```
$ cp -v salt/roots/pillar/arduino.sls.example salt/roots/pillar/arduino.sls
```

Copy vagrant file from `vagrant/examples/` and then create the vagrant box (you can change to `--provider=virtualbox` if you want to use Oracle VirtualBox provider):
```
$ cp -v vagrant/examples/Vagrantfile.arduino-box.fedora-33.x86_64.example vagrant/Vagrantfile.arduino-box
$ vagrant up --provider=libvirt
```

Provision the vagrant box:
```
$ vagrant ssh arduino-box -- sudo salt-call state.highstate
```

Install Arduino:
```
$ vagrant ssh arduino-box -- sudo salt-call state.sls arduino
```


## Starting Arduino IDE

To upload Arduino projects into the Vagrant box:
```
$ vagrant rsync
$ vagrant ssh arduino-box -- sudo salt-call state.sls arduinoprojects
```

To start Arduino IDE:
```
$ vagrant ssh arduino-box -- /opt/arduino/arduino-1.8.13/arduino
```
