from setuptools import find_packages
from setuptools import setup

setup(
    name='rover_visualizer',
    version='0.0.0',
    packages=find_packages(
        include=('rover_visualizer', 'rover_visualizer.*')),
)
