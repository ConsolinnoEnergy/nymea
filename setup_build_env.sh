# @copyright GPLv3 (c) 2022 Consolinno Energy GmbH
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

dpkg --add-architecture $1
apt-get update 
apt-get -y upgrade
apt-get install -y apt-utils gnupg
apt-key adv --keyserver keyserver.ubuntu.com --recv-key A1A19ED6
apt-get install -y software-properties-common
export VERSION_CODENAME=`cat /etc/*release | grep VERSION_CODENAME | cut -c 18-`
apt-add-repository -s "deb http://repository.nymea.io $VERSION_CODENAME main"
apt-get update
#Install crossbuild toolchain
apt-get install -y crossbuild-essential-$1
# binutils-multiarch devscripts
# Install libnymea libs and dependencies for armhf
apt-get install -y libnymea-dev:armhf 
# Dev tools need to run on host arch
apt-get install -y nymea-dev-tools 
# Install nymea-plugins build deps
# apt-get install -y \
# libboblight:armhf libboblight-dev:armhf libdrm-dev:armhf libftdi1-2:armhf libgl1-mesa-dev:armhf libgles1:armhf libgles2:armhf libglu1-mesa:armhf libglu1-mesa-dev:armhf libglvnd-core-dev:armhf libglvnd-dev:armhf libhidapi-dev:armhf libhidapi-hidraw0:armhf libhidapi-libusb0:armhf libnymea-dev:armhf libnymea-gpio:armhf libnymea-gpio-dev:armhf libnymea-mqtt:armhf libnymea-mqtt-dev:armhf libnymea-zigbee-dev:armhf libnymea-zigbee1:armhf libnymea1:armhf libopengl0:armhf libow-3.2-3:armhf libow-dev:armhf libowcapi-3.2-3:armhf libpthread-stubs0-dev:armhf libpython-stdlib:armhf libpython2-stdlib:armhf libpython2.7-minimal:armhf libpython2.7-stdlib:armhf libqt5bluetooth5:armhf libqt5concurrent5:armhf libqt5nfc5:armhf libqt5serialport5:armhf libqt5serialport5-dev:armhf libqt5test5:armhf libqt5websockets5:armhf libqt5websockets5-dev:armhf libsodium-dev:armhf libsodium23:armhf libuchardet0:armhf libudev-dev:armhf libvulkan-dev:armhf libvulkan1:armhf libx11-dev:armhf libx11-xcb-dev:armhf libxau-dev:armhf libxcb-dri2-0-dev:armhf libxcb-dri3-dev:armhf libxcb-glx0-dev:armhf libxcb-present-dev:armhf libxcb-randr0-dev:armhf libxcb-render0-dev:armhf libxcb-shape0-dev:armhf libxcb-sync-dev:armhf libxcb-xfixes0-dev:armhf libxcb1-dev:armhf libxdamage-dev:armhf libxdmcp-dev:armhf libxext-dev:armhf libxfixes-dev:armhf libxshmfence-dev:armhf libxxf86vm-dev:armhf mesa-common-dev:armhf qtbase5-dev:armhf qtconnectivity5-dev:armhf libqt5serialbus5-dev:armhf libqt5serialport5-dev:armhf libi2c-dev:armhf libnymea-energy-dev:armhf
apt-get build-dep -a$1 nymea # Might replace part of the above line
apt-get install -y git-buildpackage

# Setting up qmake
# TODO: Cleaner solution would be to use qtchooser at this point
#echo -e "/usr/lib/arm-linux-gnueabihf/qt5/bin\n/usr/lib/arm-linux-gnueabihf" >> /usr/share/qtchooser/qt5-arm-linux-gnueabihf.conf
#export QT_SELECT=qt5-arm-linux-gnueabihf
# We need the native lrelease tool
ln -sf  /usr/lib/x86_64-linux-gnu/qt5/bin/lrelease /usr/bin/lrelease
# TODO needs to be parameterized
ln -sf /usr/lib/arm-linux-gnueabihf/qt5/bin/qmake /usr/bin/qmake
export QTLIBDIR="/usr/lib/arm-linux-gnueabihf"
