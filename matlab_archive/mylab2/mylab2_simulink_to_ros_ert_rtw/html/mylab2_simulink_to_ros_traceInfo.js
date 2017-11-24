function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <Root>/Blank Message */
	this.urlHashMap["mylab2_simulink_to_ros:5"] = "mylab2_simulink_to_ros.h:144";
	/* <Root>/Blank Message1 */
	this.urlHashMap["mylab2_simulink_to_ros:9"] = "mylab2_simulink_to_ros.h:145";
	/* <Root>/Constant1 */
	this.urlHashMap["mylab2_simulink_to_ros:15"] = "mylab2_simulink_to_ros.cpp:51&mylab2_simulink_to_ros.h:62&mylab2_simulink_to_ros_data.cpp:39";
	/* <Root>/Constant2 */
	this.urlHashMap["mylab2_simulink_to_ros:17"] = "mylab2_simulink_to_ros.cpp:38&mylab2_simulink_to_ros.h:59&mylab2_simulink_to_ros_data.cpp:36";
	/* <Root>/Get Parameter */
	this.urlHashMap["mylab2_simulink_to_ros:4"] = "msg=rtwMsg_notTraceable&block=mylab2_simulink_to_ros:4";
	/* <Root>/Publish */
	this.urlHashMap["mylab2_simulink_to_ros:1"] = "mylab2_simulink_to_ros.cpp:42,48,86,99,121,130&mylab2_simulink_to_ros.h:138,146";
	/* <Root>/Publish1 */
	this.urlHashMap["mylab2_simulink_to_ros:12"] = "mylab2_simulink_to_ros.cpp:55,61,101,114,132,141&mylab2_simulink_to_ros.h:147";
	/* <Root>/Set Parameter */
	this.urlHashMap["mylab2_simulink_to_ros:3"] = "msg=rtwMsg_notTraceable&block=mylab2_simulink_to_ros:3";
	/* <Root>/Subscribe */
	this.urlHashMap["mylab2_simulink_to_ros:2"] = "mylab2_simulink_to_ros.h:148";
	/* <Root>/Subscribe1 */
	this.urlHashMap["mylab2_simulink_to_ros:13"] = "mylab2_simulink_to_ros.h:149";
	/* <Root>/motor */
	this.urlHashMap["mylab2_simulink_to_ros:6"] = "mylab2_simulink_to_ros.cpp:37";
	/* <Root>/servo */
	this.urlHashMap["mylab2_simulink_to_ros:10"] = "mylab2_simulink_to_ros.cpp:50";
	/* <S1>/Constant */
	this.urlHashMap["mylab2_simulink_to_ros:5:33"] = "mylab2_simulink_to_ros.h:53&mylab2_simulink_to_ros_data.cpp:27";
	/* <S2>/Constant */
	this.urlHashMap["mylab2_simulink_to_ros:9:33"] = "mylab2_simulink_to_ros.h:56&mylab2_simulink_to_ros_data.cpp:33";
	/* <S3>/SinkBlock */
	this.urlHashMap["mylab2_simulink_to_ros:1:31"] = "mylab2_simulink_to_ros.cpp:43,44,87,98,122,123,129&mylab2_simulink_to_ros.h:45,47";
	/* <S4>/SinkBlock */
	this.urlHashMap["mylab2_simulink_to_ros:12:31"] = "mylab2_simulink_to_ros.cpp:56,57,102,113,133,134,140&mylab2_simulink_to_ros.h:44,46";
	/* <S5>/Constant */
	this.urlHashMap["mylab2_simulink_to_ros:2:51"] = "msg=rtwMsg_notTraceable&block=mylab2_simulink_to_ros:2:51";
	/* <S5>/Enabled
Subsystem */
	this.urlHashMap["mylab2_simulink_to_ros:2:52"] = "mylab2_simulink_to_ros.h:150";
	/* <S5>/SourceBlock */
	this.urlHashMap["mylab2_simulink_to_ros:2:58"] = "msg=rtwMsg_notTraceable&block=mylab2_simulink_to_ros:2:58";
	/* <S6>/Constant */
	this.urlHashMap["mylab2_simulink_to_ros:13:51"] = "msg=rtwMsg_notTraceable&block=mylab2_simulink_to_ros:13:51";
	/* <S6>/Enabled
Subsystem */
	this.urlHashMap["mylab2_simulink_to_ros:13:52"] = "mylab2_simulink_to_ros.h:151";
	/* <S6>/SourceBlock */
	this.urlHashMap["mylab2_simulink_to_ros:13:58"] = "msg=rtwMsg_notTraceable&block=mylab2_simulink_to_ros:13:58";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "mylab2_simulink_to_ros"};
	this.sidHashMap["mylab2_simulink_to_ros"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<S1>"] = {sid: "mylab2_simulink_to_ros:5"};
	this.sidHashMap["mylab2_simulink_to_ros:5"] = {rtwname: "<S1>"};
	this.rtwnameHashMap["<S2>"] = {sid: "mylab2_simulink_to_ros:9"};
	this.sidHashMap["mylab2_simulink_to_ros:9"] = {rtwname: "<S2>"};
	this.rtwnameHashMap["<S3>"] = {sid: "mylab2_simulink_to_ros:1"};
	this.sidHashMap["mylab2_simulink_to_ros:1"] = {rtwname: "<S3>"};
	this.rtwnameHashMap["<S4>"] = {sid: "mylab2_simulink_to_ros:12"};
	this.sidHashMap["mylab2_simulink_to_ros:12"] = {rtwname: "<S4>"};
	this.rtwnameHashMap["<S5>"] = {sid: "mylab2_simulink_to_ros:2"};
	this.sidHashMap["mylab2_simulink_to_ros:2"] = {rtwname: "<S5>"};
	this.rtwnameHashMap["<S6>"] = {sid: "mylab2_simulink_to_ros:13"};
	this.sidHashMap["mylab2_simulink_to_ros:13"] = {rtwname: "<S6>"};
	this.rtwnameHashMap["<S7>"] = {sid: "mylab2_simulink_to_ros:2:52"};
	this.sidHashMap["mylab2_simulink_to_ros:2:52"] = {rtwname: "<S7>"};
	this.rtwnameHashMap["<S8>"] = {sid: "mylab2_simulink_to_ros:13:52"};
	this.sidHashMap["mylab2_simulink_to_ros:13:52"] = {rtwname: "<S8>"};
	this.rtwnameHashMap["<Root>/Blank Message"] = {sid: "mylab2_simulink_to_ros:5"};
	this.sidHashMap["mylab2_simulink_to_ros:5"] = {rtwname: "<Root>/Blank Message"};
	this.rtwnameHashMap["<Root>/Blank Message1"] = {sid: "mylab2_simulink_to_ros:9"};
	this.sidHashMap["mylab2_simulink_to_ros:9"] = {rtwname: "<Root>/Blank Message1"};
	this.rtwnameHashMap["<Root>/Constant1"] = {sid: "mylab2_simulink_to_ros:15"};
	this.sidHashMap["mylab2_simulink_to_ros:15"] = {rtwname: "<Root>/Constant1"};
	this.rtwnameHashMap["<Root>/Constant2"] = {sid: "mylab2_simulink_to_ros:17"};
	this.sidHashMap["mylab2_simulink_to_ros:17"] = {rtwname: "<Root>/Constant2"};
	this.rtwnameHashMap["<Root>/Get Parameter"] = {sid: "mylab2_simulink_to_ros:4"};
	this.sidHashMap["mylab2_simulink_to_ros:4"] = {rtwname: "<Root>/Get Parameter"};
	this.rtwnameHashMap["<Root>/Publish"] = {sid: "mylab2_simulink_to_ros:1"};
	this.sidHashMap["mylab2_simulink_to_ros:1"] = {rtwname: "<Root>/Publish"};
	this.rtwnameHashMap["<Root>/Publish1"] = {sid: "mylab2_simulink_to_ros:12"};
	this.sidHashMap["mylab2_simulink_to_ros:12"] = {rtwname: "<Root>/Publish1"};
	this.rtwnameHashMap["<Root>/Set Parameter"] = {sid: "mylab2_simulink_to_ros:3"};
	this.sidHashMap["mylab2_simulink_to_ros:3"] = {rtwname: "<Root>/Set Parameter"};
	this.rtwnameHashMap["<Root>/Subscribe"] = {sid: "mylab2_simulink_to_ros:2"};
	this.sidHashMap["mylab2_simulink_to_ros:2"] = {rtwname: "<Root>/Subscribe"};
	this.rtwnameHashMap["<Root>/Subscribe1"] = {sid: "mylab2_simulink_to_ros:13"};
	this.sidHashMap["mylab2_simulink_to_ros:13"] = {rtwname: "<Root>/Subscribe1"};
	this.rtwnameHashMap["<Root>/motor"] = {sid: "mylab2_simulink_to_ros:6"};
	this.sidHashMap["mylab2_simulink_to_ros:6"] = {rtwname: "<Root>/motor"};
	this.rtwnameHashMap["<Root>/servo"] = {sid: "mylab2_simulink_to_ros:10"};
	this.sidHashMap["mylab2_simulink_to_ros:10"] = {rtwname: "<Root>/servo"};
	this.rtwnameHashMap["<S1>/Constant"] = {sid: "mylab2_simulink_to_ros:5:33"};
	this.sidHashMap["mylab2_simulink_to_ros:5:33"] = {rtwname: "<S1>/Constant"};
	this.rtwnameHashMap["<S1>/Out"] = {sid: "mylab2_simulink_to_ros:5:34"};
	this.sidHashMap["mylab2_simulink_to_ros:5:34"] = {rtwname: "<S1>/Out"};
	this.rtwnameHashMap["<S2>/Constant"] = {sid: "mylab2_simulink_to_ros:9:33"};
	this.sidHashMap["mylab2_simulink_to_ros:9:33"] = {rtwname: "<S2>/Constant"};
	this.rtwnameHashMap["<S2>/Out"] = {sid: "mylab2_simulink_to_ros:9:34"};
	this.sidHashMap["mylab2_simulink_to_ros:9:34"] = {rtwname: "<S2>/Out"};
	this.rtwnameHashMap["<S3>/In1"] = {sid: "mylab2_simulink_to_ros:1:29"};
	this.sidHashMap["mylab2_simulink_to_ros:1:29"] = {rtwname: "<S3>/In1"};
	this.rtwnameHashMap["<S3>/SignalSpecification"] = {sid: "mylab2_simulink_to_ros:1:30"};
	this.sidHashMap["mylab2_simulink_to_ros:1:30"] = {rtwname: "<S3>/SignalSpecification"};
	this.rtwnameHashMap["<S3>/SinkBlock"] = {sid: "mylab2_simulink_to_ros:1:31"};
	this.sidHashMap["mylab2_simulink_to_ros:1:31"] = {rtwname: "<S3>/SinkBlock"};
	this.rtwnameHashMap["<S4>/In1"] = {sid: "mylab2_simulink_to_ros:12:29"};
	this.sidHashMap["mylab2_simulink_to_ros:12:29"] = {rtwname: "<S4>/In1"};
	this.rtwnameHashMap["<S4>/SignalSpecification"] = {sid: "mylab2_simulink_to_ros:12:30"};
	this.sidHashMap["mylab2_simulink_to_ros:12:30"] = {rtwname: "<S4>/SignalSpecification"};
	this.rtwnameHashMap["<S4>/SinkBlock"] = {sid: "mylab2_simulink_to_ros:12:31"};
	this.sidHashMap["mylab2_simulink_to_ros:12:31"] = {rtwname: "<S4>/SinkBlock"};
	this.rtwnameHashMap["<S5>/Constant"] = {sid: "mylab2_simulink_to_ros:2:51"};
	this.sidHashMap["mylab2_simulink_to_ros:2:51"] = {rtwname: "<S5>/Constant"};
	this.rtwnameHashMap["<S5>/Enabled Subsystem"] = {sid: "mylab2_simulink_to_ros:2:52"};
	this.sidHashMap["mylab2_simulink_to_ros:2:52"] = {rtwname: "<S5>/Enabled Subsystem"};
	this.rtwnameHashMap["<S5>/SourceBlock"] = {sid: "mylab2_simulink_to_ros:2:58"};
	this.sidHashMap["mylab2_simulink_to_ros:2:58"] = {rtwname: "<S5>/SourceBlock"};
	this.rtwnameHashMap["<S5>/Out1"] = {sid: "mylab2_simulink_to_ros:2:59"};
	this.sidHashMap["mylab2_simulink_to_ros:2:59"] = {rtwname: "<S5>/Out1"};
	this.rtwnameHashMap["<S5>/Out2"] = {sid: "mylab2_simulink_to_ros:2:60"};
	this.sidHashMap["mylab2_simulink_to_ros:2:60"] = {rtwname: "<S5>/Out2"};
	this.rtwnameHashMap["<S6>/Constant"] = {sid: "mylab2_simulink_to_ros:13:51"};
	this.sidHashMap["mylab2_simulink_to_ros:13:51"] = {rtwname: "<S6>/Constant"};
	this.rtwnameHashMap["<S6>/Enabled Subsystem"] = {sid: "mylab2_simulink_to_ros:13:52"};
	this.sidHashMap["mylab2_simulink_to_ros:13:52"] = {rtwname: "<S6>/Enabled Subsystem"};
	this.rtwnameHashMap["<S6>/SourceBlock"] = {sid: "mylab2_simulink_to_ros:13:58"};
	this.sidHashMap["mylab2_simulink_to_ros:13:58"] = {rtwname: "<S6>/SourceBlock"};
	this.rtwnameHashMap["<S6>/Out1"] = {sid: "mylab2_simulink_to_ros:13:59"};
	this.sidHashMap["mylab2_simulink_to_ros:13:59"] = {rtwname: "<S6>/Out1"};
	this.rtwnameHashMap["<S6>/Out2"] = {sid: "mylab2_simulink_to_ros:13:60"};
	this.sidHashMap["mylab2_simulink_to_ros:13:60"] = {rtwname: "<S6>/Out2"};
	this.rtwnameHashMap["<S7>/In1"] = {sid: "mylab2_simulink_to_ros:2:53"};
	this.sidHashMap["mylab2_simulink_to_ros:2:53"] = {rtwname: "<S7>/In1"};
	this.rtwnameHashMap["<S7>/Enable"] = {sid: "mylab2_simulink_to_ros:2:54"};
	this.sidHashMap["mylab2_simulink_to_ros:2:54"] = {rtwname: "<S7>/Enable"};
	this.rtwnameHashMap["<S7>/Out1"] = {sid: "mylab2_simulink_to_ros:2:55"};
	this.sidHashMap["mylab2_simulink_to_ros:2:55"] = {rtwname: "<S7>/Out1"};
	this.rtwnameHashMap["<S8>/In1"] = {sid: "mylab2_simulink_to_ros:13:53"};
	this.sidHashMap["mylab2_simulink_to_ros:13:53"] = {rtwname: "<S8>/In1"};
	this.rtwnameHashMap["<S8>/Enable"] = {sid: "mylab2_simulink_to_ros:13:54"};
	this.sidHashMap["mylab2_simulink_to_ros:13:54"] = {rtwname: "<S8>/Enable"};
	this.rtwnameHashMap["<S8>/Out1"] = {sid: "mylab2_simulink_to_ros:13:55"};
	this.sidHashMap["mylab2_simulink_to_ros:13:55"] = {rtwname: "<S8>/Out1"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
