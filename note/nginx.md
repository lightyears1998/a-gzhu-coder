# Nginx笔记

## `nginx.conf`

使用PHP-CGI

```conf
# pass the PHP scripts to FastCGI server listening on 127.0.0.1:9000
#
location ~ \.php$ {
    root           D:/BitBucket/img.qfstudio.net;
    fastcgi_pass   127.0.0.1:9000;
    fastcgi_index  index.php;
    fastcgi_param  SCRIPT_FILENAME  $document_root$fastcgi_script_name;
    include        fastcgi_params;
}
```

Windows上的路径使用正斜杠为宜

```conf
location / {
    root   D:/BitBucket/img.qfstudio.net;
    index  index.html index.htm index.php;
}
```

### Windows配置

- 可以使用`winsw`或者`nssm`将`nginx.exe`包装成服务
