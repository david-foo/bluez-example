#include<unistd.h>
#include<bluetooth/bluetooth.h>
#include<bluetooth/sdp.h>
#include<bluetooth/sdp_lib.h>
sdp_session_t * register_service()
{
	uint32_t svc_uuid_int[]={0,0,0,0xABCD};
	uint8_t rfcomm_channel=11;
	const char * service_name="Roto-RooterDataRouter";
	const char * svc_dsc="Anexperimentalplumbingrouter";
	const char * service_prov="Roto-Rooter";
	uuid_t root_uuid,l2cap_uuid,rfcomm_uuid,svc_uuid,
	svc_class_uuid;
	sdp_list_t * l2cap_list=0,
	 * rfcomm_list=0,
	 * root_list=0,
	 * proto_list=0,
	 * access_proto_list=0,
	 * svc_class_list=0,
	 * profile_list=0;

	sdp_data_t * channel=0;
	sdp_profile_desc_t profile;
	sdp_record_t record={0};
	sdp_session_t * session=0;
	//setthegeneralserviceID
	sdp_uuid128_create(&svc_uuid,&svc_uuid_int);
	sdp_set_service_id(&record,svc_uuid);
	//settheserviceclass
	sdp_uuid16_create(&svc_class_uuid,SERIAL_PORT_SVCLASS_ID);
	svc_class_list=sdp_list_append(0,&svc_class_uuid);
	sdp_set_service_classes(&record,svc_class_list);
	//settheBluetoothprofileinformation
	sdp_uuid16_create(&profile.uuid,SERIAL_PORT_PROFILE_ID);
	profile.version=0x0100;
	profile_list=sdp_list_append(0,&profile);
	sdp_set_profile_descs(&record,profile_list);
	//maketheservicerecordpubliclybrowsable
	sdp_uuid16_create(&root_uuid,PUBLIC_BROWSE_GROUP);
	root_list=sdp_list_append(0,&root_uuid);
	sdp_set_browse_groups(&record,root_list);
	//setl2capinformation
	sdp_uuid16_create(&l2cap_uuid,L2CAP_UUID);
	l2cap_list=sdp_list_append(0,&l2cap_uuid);
	proto_list=sdp_list_append(0,l2cap_list);
	//registertheRFCOMMchannelforRFCOMMsockets
	sdp_uuid16_create(&rfcomm_uuid,RFCOMM_UUID);
	channel=sdp_data_alloc(SDP_UINT8,&rfcomm_channel);
	rfcomm_list=sdp_list_append(0,&rfcomm_uuid);
	sdp_list_append(rfcomm_list,channel);
	sdp_list_append(proto_list,rfcomm_list);
	access_proto_list=sdp_list_append(0,proto_list);
	sdp_set_access_protos(&record,access_proto_list);
	//setthename,provider,anddescription
	sdp_set_info_attr(&record,service_name,service_prov,svc_dsc);
	//connecttothelocalSDPserver,registertheservicerecord,


	
	//anddisconnect
	session=sdp_connect(BDADDR_ANY,BDADDR_LOCAL,SDP_RETRY_IF_BUSY);
	sdp_record_register(session,&record,0);
	//cleanup
	sdp_data_free(channel);
	sdp_list_free(l2cap_list,0);
	sdp_list_free(rfcomm_list,0);
	sdp_list_free(root_list,0);
	sdp_list_free(access_proto_list,0);
	sdp_list_free(svc_class_list,0);
	sdp_list_free(profile_list,0);
	return session;
	}
int main()
{
	sdp_session_t * session=register_service();
	sleep(5);
	sdpclose(session);
	return 0;
}
	
	
	
	
	
