import time, sys, os

# ros
from ros import rosbag
import roslib
import rospy
roslib.load_manifest('sensor_msgs')
from sensor_msgs.msg import Image
from cv_bridge import CvBridge

# opencv
import cv2

def GetFilesFromDir(dir):
    '''Generates a list of files from the directory'''
    print( "Searching directory %s" % dir )
    all = []
    left_files = []
    right_files = []
    if os.path.exists(dir):
        for path, names, files in os.walk(dir):
            for f in sorted(files):
                if os.path.splitext(f)[1] in ['.bmp', '.png', '.jpg', '.ppm']:
                    if 'left' in f or 'left' in path:
                        left_files.append( os.path.join( path, f ) )
                    elif 'right' in f or 'right' in path:
                        right_files.append( os.path.join( path, f ) )
                    all.append( os.path.join( path, f ) )
    return all, left_files, right_files


def CreateStereoBag(left_imgs, right_imgs, bagname):
    '''Creates a bag file containing stereo image pairs'''
    bag =rosbag.Bag(bagname, 'w')

    try:
        for i in range(len(left_imgs)):
            print("Adding %s" % left_imgs[i])
            img_left = cv2.imread(left_imgs[i])
            img_right = cv2.imread(right_imgs[i])

            bridge = CvBridge()

            Stamp = roslib.rostime.Time.from_sec(time.time())

            img_msg_left = Image()
            img_msg_left = bridge.cv2_to_imgmsg(img_left, "bgr8")
            img_msg_left.header.seq = i
            img_msg_left.header.stamp = Stamp
            img_msg_left.header.frame_id = "camera/left"

            img_msg_right = Image()
            img_msg_right = bridge.cv2_to_imgmsg(img_right, "bgr8")
            img_msg_right.header.seq = i
            img_msg_right.header.stamp = Stamp
            img_msg_right.header.frame_id = "camera/right"

            bag.write('camera/left/image_raw', img_msg_left, Stamp)
            bag.write('camera/right/image_raw', img_msg_right, Stamp)
            time.sleep(0.1) # [s]
    finally:
        bag.close()


def CreateMonoBag(imgs, bagname):
    '''Creates a bag file with camera images'''
    bag =rosbag.Bag(bagname, 'w')

    try:
        for i in range(len(imgs)):
            print("Adding %s" % imgs[i])
            img = cv2.imread(imgs[i])
            bridge = CvBridge()

            Stamp = rospy.rostime.Time.from_sec(time.time())
            img_msg = Image()
            img_msg = bridge.cv2_to_imgmsg(img, "bgr8")
            img_msg.header.seq = i
            img_msg.header.stamp = Stamp
            img_msg.header.frame_id = "camera"
	
            bag.write('camera/image_raw', img_msg, Stamp)
            time.sleep(0.1) # [s]
    finally:
        bag.close()       


def CreateBag(args):
    '''Creates the actual bag file by successively adding images'''
    all_imgs, left_imgs, right_imgs = GetFilesFromDir(args[0])
    if len(all_imgs) <= 0:
        print("No images found in %s" % args[0])
        exit()

    if len(left_imgs) > 0 and len(right_imgs) > 0:
        # create bagfile with stereo camera image pairs
        CreateStereoBag(left_imgs, right_imgs, args[1])
    else:
        # create bagfile with mono camera image stream
        CreateMonoBag(all_imgs, args[1])        

if __name__ == "__main__":
    if len( sys.argv ) == 3:
        CreateBag( sys.argv[1:])
    else:
        print( "Usage: img2bag imagedir bagfilename")
