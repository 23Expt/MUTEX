#!/bin/bash
#Path ke named pipe
PIPE="/tmp/mypipe"
#Membuat named pipe jika belum ada
if [[ ! -p $PIPE ]]; then
  mkfifo $PIPE
fi
#Fungsi untuk pembaca
pembaca () {
  while true; do
    if read baris <$PIPE; then
      echo "Pembaca menerima: $baris"
    fi
  done
}
#Fungsi untuk penulis
penulis() {
  for (( i = 1; i <= 5; i++ )); do
    echo "Pesan $i" > $PIPE
    sleep 1
  done
}
#Menjalankan fungsi pembaca di background
pembaca &
PID_PEMBACA=$!
#Menjalankan fungsi penulis
penulis
#Membersihkan setelah selesai
kill $PID_PEMBACA
rm $PIPE
echo "IPC selesai."