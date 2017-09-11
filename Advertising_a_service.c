#include<unistd.h>
#include<bluetooth/bluetooth.h>
#include<bluetooth/sdp.h>
#include<bluetooth/sdplib.h>
sdp_session_t * register_service()
{
	uint32_t svc_uuid_int[]={0,0,0,0xABCD};
	uint8_trfcomm_channel=11;
	constchar * service_name="Roto-RooterDataRouter";
	constchar * svc_dsc="Anexperimentalplumbingrouter";
	constchar * service_prov="Roto-Rooter";
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
	sdp_profile_desc_tprofile;
	sdp_record_trecord={0};
	sdp_session_t * session=0;
	//setthegeneralserviceID
	sdpuuid128create(&svc_uuid,&svc_uuid_int);
	sdp_set_service_id(&record,svc_uuid);
	//settheserviceclass
	sdp_uuid16_create(&svc_class_uuid,SERIAL_PORT_SVCLASS_ID);
	svc_class_list=sdplistappend(0,&svc_class_uuid);
	sdpsetserviceclasses(&record,svc_class_list);
	//settheBluetoothprofileinformation
	sdp_uuid16_create(&profile.uuid,SERIAL_PORT_PROFILE_ID);
	profile.version=0x0100;
	profile_list=sdplistappend(0,&profile);
	sdpsetprofiledescs(&record,profile_list);
	//maketheservicerecordpubliclybrowsable
	sdp_uuid16_create(&root_uuid,PUBLIC_BROWSE_GROUP);
	root_list=sdplistappend(0,&root_uuid);
	sdpsetbrowsegroups(&record,root_list);
	//setl2capinformation
	sdp_uuid16_create(&l2cap_uuid,L2CAP_UUID);
	l2cap_list=sdplistappend(0,&l2cap_uuid);
	proto_list=sdplistappend(0,l2cap_list);
	//registertheRFCOMMchannelforRFCOMMsockets
	sdp_uuid16_create(&rfcomm_uuid,RFCOMM_UUID);
	channel=sdpdataalloc(SDP_UINT8,&rfcomm_channel);
	rfcomm_list=sdplistappend(0,&rfcomm_uuid);
	sdplistappend(rfcomm_list,channel);
	sdplistappend(proto_list,rfcomm_list);
	access_proto_list=sdplistappend(0,proto_list);
	sdpsetaccessprotos(&record,access_proto_list);
	//setthename,provider,anddescription
	sdpsetinfoattr(&record,service_name,service_prov,svc_dsc);
	//connecttothelocalSDPserver,registertheservicerecord,


	
	//anddisconnect
	session=sdpconnect(BDADDR_ANY,BDADDR_LOCAL,SDP_RETRY_IF_BUSY);
	sdprecordregister(session,&record,0);
	//cleanup
	sdp_data_free(channel);
	sdplistfree(l2cap_list,0);
	sdplistfree(rfcomm_list,0);
	sdplistfree(root_list,0);
	sdplistfree(access_proto_list,0);
	sdplistfree(svc_class_list,0);
	sdplistfree(profile_list,0);
	returnsession;
	}
int main()
{
	sdp_session_t * session=register_service();
	sleep(5);
	sdpclose(session);
	return0;
}
	
	
	
	
	
