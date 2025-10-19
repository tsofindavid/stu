sshpass -f ~/.passwd -e sftp -oBatchMode=no -b - xtsofin@webte1.fei.stuba.sk << !
   rmdir public_html
   mkdir public_html
   cd public_html
   cp index.html .
   cp -r cv_1 .
!