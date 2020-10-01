# Introduction

This project involves developing an Enterprise Service Bus (ESB) in C.

## Setting up the environment for running the app

The following instructions assume that you are working on an Ubuntu machine, and are in the sudoers group (or have root-access).

### Installing essential libraries that you will need

1. Open a shell and run `sudo apt update`
1. Ensure that you have installed the essential headers and libraries: `sudo apt install build-essential`
1. Install the XML library ([libxml2](https://askubuntu.com/questions/733169/how-to-install-libxml2-in-ubuntu-15-10)) which will be used for parsing and handling xml files(BMD requests) received via HTTP.
1. The app uses MySQL database. Install [MySQL](https://www.digitalocean.com/community/tutorials/how-to-install-mysql-on-ubuntu-18-04) on your machine.
1. Install [cURL](https://www.cyberciti.biz/faq/how-to-install-curl-command-on-a-ubuntu-linux/). The modules that send data over different protocols use cURL.
1. Install required modules for creating SFTP server and create a local [SFTP server](https://linuxconfig.org/how-to-setup-sftp-server-on-ubuntu-20-04-focal-fossa-linux#:~:text=You%20can%20use%20your%20preferred,the%20window%20and%20click%20connect.).(More details in setup)
1. Install Kore Web framework as [described here](https://docs.kore.io/3.3.1/install.html). This will be used for creating an HTTP endpoint for receiving the requests for the ESB.
1. The app comes along with a unit testing framework [munit](https://nemequ.github.io/munit/#getting-started). You don't need to install any.

### Customized setup

The app uses the default setup. Feel free to customize them to your convenience.
##### 1. MYSQL

 Default USER: root
 
 Default PASS:
 
 (No password set for convenience. You can either remove the password in your machine or change source.)
 
 To change password and other configurations goto `satluj/esb_app/src/db_access/connection.h`
#### 2.SFTP

Default USER: narmadasftp

Default PASS: narmada1

To be able to upload over SFTP with default settings, you should create the above user with the given password at the localhost.
```
$ sudo useradd -m narmadasftp -g sftp
$ sudo passwd sftpuser
New password: 
Retype new password: 
passwd: password updated successfully
```
For detailed instructions, [visit here](https://linuxconfig.org/how-to-setup-sftp-server-on-ubuntu-20-04-focal-fossa-linux).

To change the change configurations, please goto `satluj/esb_app/src/adapter/sftp_upload.c` and edit as required.

## Source code-layout
 The code-layout appears as below when you clone into this repo and built the kore app.
 The layout within `satluj/esb_app:`
```
.
├── assets
├── bmd_files
│   ├── bmd10.xml
│   ├── bmd11.xml
│   ├── bmd12.xml
│   ├── bmd13.xml
│   ├── bmd14.xml
│   ├── bmd15.xml
│   ├── bmd16.xml
│   ├── bmd17.xml
│   ├── bmd18.xml
│   ├── bmd1.xml
│   ├── bmd2.xml
│   ├── bmd3.xml
│   ├── bmd4.xml
│   ├── bmd5.xml
│   ├── bmd6.xml
│   ├── bmd7.xml
│   ├── bmd8.xml
│   ├── bmd9.xml
│   ├── input_requests.sh
│   └── status.sh
├── cert
│   ├── key.pem
│   └── server.pem
├── conf
│   ├── build.conf
│   └── esb_app.conf
├── dh2048.pem
├── esb_app.so
├── kore.pid
├── src
│   ├── adapter
│   │   ├── adapter.h
│   │   ├── call_destination_service.c
│   │   ├── email.c
│   │   ├── function_lookup.c
│   │   ├── http_post.c
│   │   ├── Makefile
│   │   ├── Makefile.email
│   │   ├── Makefile.http
│   │   ├── Makefile.http_post
│   │   ├── Makefile.sftp_upload
│   │   ├── Makefile.test
│   │   ├── Makefile.transform
│   │   ├── sftp_upload.c
│   │   ├── somefile.txt
│   │   ├── test_adapter.c
│   │   └── transform.c
│   ├── bmd_handler
│   │   ├── bmd.h
│   │   ├── is_bmd_valid.c
│   │   ├── Makefile
│   │   ├── test_bmd.c
│   │   └── xml_handler.c
│   ├── db_access
│   │   ├── connector.h
│   │   ├── create_schema.sql
│   │   ├── db_connect.c
│   │   ├── fetch_new_esb_request.c
│   │   ├── fetch_transform_config.c
│   │   ├── fetch_transport_config.c
│   │   ├── get_active_route_id.c
│   │   ├── get_status.c
│   │   ├── has_transform_config.c
│   │   ├── has_transport_config.c
│   │   ├── insert_test.sql
│   │   ├── insert_to_esb_request.c
│   │   ├── Makefile
│   │   ├── Makefile.db_connect
│   │   ├── Makefile.test
│   │   ├── select_active_routes.c
│   │   ├── select_all_transport_config.c
│   │   ├── test_db_access.c
│   │   └── update_esb_request.c
│   ├── esb
│   │   ├── cleanup.c
│   │   ├── esb.c
│   │   ├── esb.h
│   │   ├── Makefile
│   │   ├── Makefile.esb
│   │   ├── test_esb.c
│   │   └── worker.c
│   ├── esb_app.c
│   ├── Makefile
│   ├── msuit.c
│   └── test
│       ├── munit.c
│       └── munit.h
└── tmp_files
```


## Creating a workspace with the sample code

You can execute the following steps on a shell (on Ubuntu):
```bash
# Install required libraries
sudo apt update
sudo apt install build-essential
sudo apt install libssl-dev
sudo apt install wget
sudo apt install curl

# Download the kodev sources
wget https://kore.io/releases/kore-3.2.0.tar.gz
tar -xf kore-3.2.0.tar.gz
cd kore-3.2.0/

# Build and install kodev
make
sudo make install

# Change directories into a working folder
cd /path/to/where/you/want/to/work

# Fetch the code from this repository
git clone https://github.com/nho2020/satluj.git
cd satluj/esb_app/src/db_access
mysql -u root -p
Enter password: 
Welcome to the MySQL monitor.  Commands end with ; or \g.
Your MySQL connection id is 162
Server version: 8.0.21-0ubuntu0.20.04.4 (Ubuntu)

Copyright (c) 2000, 2020, Oracle and/or its affiliates. All rights reserved.

Oracle is a registered trademark of Oracle Corporation and/or its
affiliates. Other names may be trademarks of their respective
owners.

Type 'help;' or '\h' for help. Type '\c' to clear the current input statement.

mysql> source insert_test.sql;

#insert_test contains database schema creation and populating tables.

# Build and run the kodev application
cd satluj/esb_app
#Within esb_app run the following.
kodev build
kodev run
```

Open another shell window and run:
Within satluj/esb_app/bmd_files/
Run the following command sends the requests.

`curl --insecure -F "bmd_file=@bmd1.xml" https://localhost:8888/bmd`

Check the logs in the first shell; the log shows how BMD is received and being processed.

The directory satluj/esb_app/bmd_files  has bmd files marked 1 to 18.

1 to 9 files contain  payload of IFSC code of Indian banks. 

10 to 18 files contain payload details of country code for currency.

The same directory also has a shell script to give multiple files as input.
 You can run it by `./input_requests.sh`
 
There are also commands to know the status info. check `status.sh`


