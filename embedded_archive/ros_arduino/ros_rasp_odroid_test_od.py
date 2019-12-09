import rospy

def getUltra(data):
	ult = data.data


def rosTest():
	rospy.init_node('odroid_py_test_node', anonymous=True)
	rospy.Subscriber('getUltraData', Float32, getUltra)
	pub = rospy.Publisher('setServoAngle', Int32, queue_size=10)

rosTest()
while not rospy.is_shutdown():
	if ult > 2.5 and ult < 12.5:
		pub.publish(ult)




