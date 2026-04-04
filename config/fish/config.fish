source /usr/share/cachyos-fish-config/cachyos-config.fish

functions -e fish_greeting

function proxy_on
    set -gx http_proxy http://127.0.0.1:7890
    set -gx https_proxy http://127.0.0.1:7890
    set -gx all_proxy socks5://127.0.0.1:7890
end

function proxy_off
    set -e http_proxy
    set -e https_proxy
    set -e all_proxy
end

set -gx GOPATH $HOME/.local/share/go
set -gx NPM_CONFIG_PREFIX $HOME/.local/share/npm

fish_add_path $GOPATH/bin
fish_add_path $NPM_CONFIG_PREFIX/bin
