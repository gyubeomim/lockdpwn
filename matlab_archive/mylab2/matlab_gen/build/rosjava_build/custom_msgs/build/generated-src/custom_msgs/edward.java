package custom_msgs;

public interface edward extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "custom_msgs/edward";
  static final java.lang.String _DEFINITION = "std_msgs/Float64 x_ed\nstd_msgs/Float64 y_ed\nstd_msgs/Float64 z_ed\n";
  static final boolean _IS_SERVICE = false;
  static final boolean _IS_ACTION = false;
  std_msgs.Float64 getXEd();
  void setXEd(std_msgs.Float64 value);
  std_msgs.Float64 getYEd();
  void setYEd(std_msgs.Float64 value);
  std_msgs.Float64 getZEd();
  void setZEd(std_msgs.Float64 value);
}
