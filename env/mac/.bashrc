if [ -d ${HOME}/bin ] 
then
    export PATH=${HOME}/bin:$PATH
fi

HISTCONTROL=ignoreboth
HISTSIZE=100000
HISTFILESIZE=200000

alias ls='ls -G'
alias ll='ls -lhF'
alias la='ls -AF'
alias lla='ls -AlhF'
alias lo='ls -AlF'
alias wget='curl -OL'
alias emn='emacs -nw'

VENVWRAP=/usr/local/bin/virtualenvwrapper.sh
if [ $VENVWRAP ]
then
	export WORKON_HOME=$HOME/workspace/.virtualenvs
	source $VENVWRAP
fi

## Android SDK
#export ANDROID_SDK_VERSION=$(brew info android-sdk | grep "stable" | awk '{ print $3 }')
#export ANDROID_HOME=/usr/local/Cellar/android-sdk/${ANDROID_SDK_VERSION}
#export PATH=${PATH}:${ANDROID_HOME}/platform-tools
#export PATH=${PATH}:${ANDROID_HOME}/tools
