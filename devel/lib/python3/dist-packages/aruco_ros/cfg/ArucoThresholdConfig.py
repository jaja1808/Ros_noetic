## *********************************************************
##
## File autogenerated for the aruco_ros package
## by the dynamic_reconfigure package.
## Please do not edit.
##
## ********************************************************/

from dynamic_reconfigure.encoding import extract_params

inf = float('inf')

config_description = {'name': 'Default', 'type': '', 'state': True, 'cstate': 'true', 'id': 0, 'parent': 0, 'parameters': [{'name': 'min_image_size', 'type': 'double', 'default': 0.02, 'level': 0, 'description': 'minimum size of marker as a % of image area', 'min': 0.0, 'max': 1.0, 'srcline': 291, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'edit_method': '', 'ctype': 'double', 'cconsttype': 'const double'}, {'name': 'normalizeImage', 'type': 'bool', 'default': True, 'level': 0, 'description': 'normalizeImage', 'min': False, 'max': True, 'srcline': 291, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'edit_method': '', 'ctype': 'bool', 'cconsttype': 'const bool'}, {'name': 'dctComponentsToRemove', 'type': 'int', 'default': 2, 'level': 0, 'description': 'DCT components to remove', 'min': 1, 'max': 4, 'srcline': 291, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'edit_method': '', 'ctype': 'int', 'cconsttype': 'const int'}, {'name': 'degree', 'type': 'int', 'default': 0, 'level': 0, 'description': 'Degree to rotate', 'min': 0, 'max': 360, 'srcline': 291, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'edit_method': '', 'ctype': 'int', 'cconsttype': 'const int'}, {'name': 'detection_mode', 'type': 'int', 'default': 1, 'level': 0, 'description': 'The detection mode , affects speed and reliability', 'min': 0, 'max': 2, 'srcline': 291, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'edit_method': "{'enum': [{'name': 'Normal', 'type': 'int', 'value': 0, 'srcline': 12, 'srcfile': '/home/esirem/Documents/Project_ws/catkin_ws/src/aruco_ros/aruco_ros/cfg/ArucoThreshold.cfg', 'description': '', 'ctype': 'int', 'cconsttype': 'const int'}, {'name': 'Fast', 'type': 'int', 'value': 1, 'srcline': 13, 'srcfile': '/home/esirem/Documents/Project_ws/catkin_ws/src/aruco_ros/aruco_ros/cfg/ArucoThreshold.cfg', 'description': '', 'ctype': 'int', 'cconsttype': 'const int'}, {'name': 'Video_Fast', 'type': 'int', 'value': 2, 'srcline': 14, 'srcfile': '/home/esirem/Documents/Project_ws/catkin_ws/src/aruco_ros/aruco_ros/cfg/ArucoThreshold.cfg', 'description': '', 'ctype': 'int', 'cconsttype': 'const int'}], 'enum_description': 'detection_mode enum'}", 'ctype': 'int', 'cconsttype': 'const int'}], 'groups': [], 'srcline': 246, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'class': 'DEFAULT', 'parentclass': '', 'parentname': 'Default', 'field': 'default', 'upper': 'DEFAULT', 'lower': 'groups'}

min = {}
max = {}
defaults = {}
level = {}
type = {}
all_level = 0

#def extract_params(config):
#    params = []
#    params.extend(config['parameters'])
#    for group in config['groups']:
#        params.extend(extract_params(group))
#    return params

for param in extract_params(config_description):
    min[param['name']] = param['min']
    max[param['name']] = param['max']
    defaults[param['name']] = param['default']
    level[param['name']] = param['level']
    type[param['name']] = param['type']
    all_level = all_level | param['level']

ArucoThreshold_Normal = 0
ArucoThreshold_Fast = 1
ArucoThreshold_Video_Fast = 2