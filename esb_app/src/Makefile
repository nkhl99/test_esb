ADAPTER = ./adapter/email.c ./adapter/http_post.c ./adapter/transform.c ./adapter/call_destination_service.c 
BMD = ./bmd_handler/is_bmd_valid.c ./bmd_handler/xml_handler.c 
DB_ACCESS = ./db_access/get_active_route_id.c ./db_access/fetch_transport_config.c ./db_access/has_transform_config.c \
./db_access/has_transport_config.c ./db_access/db_connect.c ./db_access/insert_to_esb_request.c ./db_access/update_esb_request.c \
./db_access/fetch_transform_config.c ./db_access/fetch_new_esb_request.c ./db_access/./get_status.c
INCLUDE = `mysql_config --cflags --libs` `xml2-config --cflags` `xml2-config --libs`
tests: test_all.c	
	gcc ${ADAPTER} ${BMD} ${DB_ACCESS} test_all.c -lcurl -o tests ${INCLUDE} ./test/munit.c
clean:
	rm tests .*o *.json payload_4ac26
