DB_ACCESS = ../db_access/get_active_route_id.c ../db_access/update_esb_request.c         \
            ../db_access/has_transport_config.c ../db_access/has_transform_config.c      \
			../db_access/insert_to_esb_request.c ../db_access/fetch_new_esb_request.c    \
			../db_access/fetch_transform_config.c ../db_access/fetch_transport_config.c  \
			../db_access/db_connect.c
XML_HANDLER = ../bmd_handler/xml_handler.c ../bmd_handler/is_bmd_valid.c

ADAPTER = ../adapter/transform.c ../adapter/email.c                   \
         ../adapter/call_destination_service.c ../adapter/http_post.c \
		 ../adapter/function_lookup.c  ../adapter/sftp_upload.c

INCLUDE = `mysql_config --cflags --libs` `xml2-config --cflags` `xml2-config --libs` ./cleanup.c 

work: worker.c valid.o
	gcc worker.c ${XML_HANDLER} -o worker ${DB_ACCESS} ${INCLUDE} ${ADAPTER} -lcurl
valid.o: ${XML_HANDLER} 
	gcc -c ${DB_ACCESS} ${XML_HANDLER} ${INCLUDE} ${ADAPTER}
clean:
	rm *.o worker 
