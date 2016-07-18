
* essentials

	~~~
sudo pacman -S git
sudo pacman -S busybox
sudo pacman -S bash-completion
sudo pacman -S openssh
sudo pacman -S netsurf
sudo pacman -S emacs
~~~

* video driver

	~~~
sudo pacman -S xf86-video-vesa
sudo pacman -S xf86-video-s3
~~~

* X
	* Desktop Manager
		* [SLiM](https://wiki.archlinuxjp.org/index.php/SLiM)
			* don't use it !
		* [LightDM](https://wiki.archlinuxjp.org/index.php/LightDM)

	~~~
sudo pacman -S xorg-server
sudo pacman -S lightdm lightdm-gtk-greeter
systemctl enable lightdm.service
sudo pacman -S xfce4
cp -a /etc/X11/xinit/xinitrc ~/.xinitrc
~~~

* edit /etc/lightdm/lightdm.conf

	~~~
greeter-session=lightdm-gtk-greeter
~~~

* edit ~/.xinitrc

	~~~
#twm &
#xclock -geometry 50x50-1+1 &
#xterm -geometry 80x50+494+51 &
#xterm -geometry 80x20+494-0 &
#exec xterm -geometry 80x66+0+0 -name login

exec startxfce4
~~~

* ALPS touchpad setting

	~~~
sudo pacman -S xf86-input-synaptics
sudo cp -a /usr/share/X11/xorg.conf.d/50-synaptics.conf /etc/X11/xorg.conf.d/
~~~

* netsurf setting

	~~~
cd .config/netsurf/
ln -s /tmp/Cookies
ln -s /tmp/URLs
~~~

* python

	~~~
sudo pacman -S python2
~~~

* [timesyncd (systemd)](http://wiki.archlinuxjp.org/index.php/Systemd-timesyncd)
	* clock display on right-up -> Properties -> Timezone
		* not Tokyo but **Asia/Tokyo**.

	~~~
sudo vi /etc/systemd/timesyncd.conf
 ->	NTP=ntp.nict.jp

timedatectl status
timedatectl set-ntp true
timedatectl status
~~~
