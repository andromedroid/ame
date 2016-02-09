
* [TensorFlow をアプリで使ってみる](http://blog.guildworks.jp/2015/11/16/tensorflow/)
	* [install android sdk/ndk](http://developer.android.com/intl/ja/sdk/)

	~~~
sudo apt install lib32stdc++6 lib32ncurses5 lib32z1
~~~
	* install bazel

	~~~
dpkg --info bazel_0.1.4-jdk7-linux-x86_64.deb
sudo apt install build-essential openjdk-7-jdk openjdk-7-source zlib1g-dev zip
sudo dpkg -i bazel_0.1.4-jdk7-linux-x86_64.deb
~~~
	* download tensorflow repository

	~~~
cd ~/_git/tensorflow/
git clone --recurse-submodules https://github.com/tensorflow/tensorflow.git
~~~
	* [download assets](https://github.com/tensorflow/tensorflow/tree/master/tensorflow/examples/android)

	~~~
wget https://storage.googleapis.com/download.tensorflow.org/models/inception5h.zip
unzip inception5h.zip -d tensorflow/tensorflow/examples/android/assets/
cd tensorflow/
~~~
	* build tensorflow

	~~~
./configure
bazel build --jobs 2 //tensorflow/examples/android:tensorflow_demo
~~~
