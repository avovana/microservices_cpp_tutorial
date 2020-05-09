#!/bin/bash

# example
## ./install_environment.sh inventory/localhost.yml

main() {
      ansible_config=$1
      printf "Ansible config: $ansible_config\n"
      time ansible-playbook 01_install_env.yml -i $ansible_config
      echo $(date)
}

main ${@}

