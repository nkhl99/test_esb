INCLUDE = `mysql_config --cflags --libs` `xml2-config --cflags` `xml2-config --libs`
test: get_status.c
	gcc get_status.c -o get ${INCLUDE} db_connect.c
clean:
	rm get