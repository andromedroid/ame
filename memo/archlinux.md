
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

* ALPS touchpad setting

	~~~
sudo pacman -S xf86-input-synaptics
sudo cp -a /usr/share/X11/xorg.conf.d/50-synaptics.conf /etc/X11/xorg.conf.d/
~~~

* X

	~~~
sudo pacman -S xorg-server
sudo pacman -S slim
sudo pacman -S xfce4
echo "exec startxfce4" > ~/.xinitrc
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
