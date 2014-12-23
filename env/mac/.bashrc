if [ -d ${HOME}/bin ] 
then
    export PATH=${HOME}/bin:$PATH
fi

alias ls='ls -G'
alias ll='ls -lhF'
alias la='ls -AF'
alias lla='ls -AlhF'
alias lo='ls -AlF'
alias emn='emacs -nw'

export HOMEBREW_GITHUB_API_TOKEN="17c00e23edc6220ab480aa028506e11e1425fcf8"

export JAVA_HOME=$(/usr/libexec/java_home -v 1.7)

export ANDROID_SDK_VERSION=$(brew info android-sdk | grep "stable" | awk '{ print $3 }')
export ANDROID_HOME=/usr/local/Cellar/android-sdk/${ANDROID_SDK_VERSION}
export PATH=${PATH}:${ANDROID_HOME}/platform-tools
export PATH=${PATH}:${ANDROID_HOME}/tools
