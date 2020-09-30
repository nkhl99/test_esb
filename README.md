# satluj
Introduction
This project involves developing an Enterprise Service Bus (ESB) in C.

Setting up the environment for running the app
The following instructions assume that you are working on an Ubuntu machine, and are in the sudoers group (or have root-access).

Installing essential libraries that you will need

Open a shell and run sudo apt update

Ensure that you have installed the essential headers and libraries: sudo apt install build-essential

Install the XML library (libxml2) which will be used for parsing and handling xml files(BMD requests) received via HTTP.

The app uses MySQL database. Install MySQL on your machine.

Install cURL. The modules that send data over different protocols use cURL.

The app uses the default setup. Feel free to customize them to your convenience.

1. MYSQL

Default USER: root

Default PASS:sunny

Creating a workspace with the sample code

You can execute the following steps on a shell (on Ubuntu):

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

# Change directories into a working folder

cd /path/to/where/you/want/to/work

# Fetch the code from this repository

git clone https://github.com/nho2020/satluj.git

cd satluj/esb_app/src/db_access

mysql -u root -p

Enter password: sunny

Welcome to the MySQL monitor.  Commands end with ; or \g.

Your MySQL connection id is 162

Server version: 8.0.21-0ubuntu0.20.04.4 (Ubuntu)

Copyright (c) 2000, 2020, Oracle and/or its affiliates. All rights reserved.

Oracle is a registered trademark of Oracle Corporation and/or its affiliates. Other names may be trademarks of their respective owners.

Type 'help;' or '\h' for help. Type '\c' to clear the current input statement.

mysql> source insert_test.sql;

#insert_test contains database schema creation and populating tables.
