from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
import os
from ament_index_python.packages import get_package_share_directory
from launch_ros.parameter_descriptions import ParameterValue
from launch.substitutions import Command, LaunchConfiguration

def generate_launch_description():

    model_arg = DeclareLaunchArgument(
        name="model",
        default_value=os.path.join(get_package_share_directory("rocket_description"), "urdf", "rocket_model.urdf.xacro"),
        description="Absolute path to rocket URDF file"
    )
    #convert xacro to urdf
    robot_description = ParameterValue(Command(["xacro ", LaunchConfiguration("model")]), value_type=str)

    robot_state_publisher = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        parameters=[{"robot_description": robot_description}]
    )




    return LaunchDescription([
        model_arg,
        robot_state_publisher
    ])