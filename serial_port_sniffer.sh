# https://github.com/geoffmeyers/interceptty # tool
# http://rpm.pbone.net/manpage_idpl_9661674_numer_1_nazwa_interceptty.html # man page
# https://hackaday.com/2022/09/07/linux-fu-eavesdropping-on-serial/ # tutorial


FRONTEND=/dev/ttyS0  # Порт, имитирующий устройство (для подключения во время прослушки)
BACKEND=/dev/ttyUSB0  # Прослушиваемое устройство

# sudo chmod a+rw /dev/ttyUSB0

echo "Traffic from $FRONTEND now are forwarding to $BACKEND through interceptty tool. You will see all traffic here."
sudo ./interceptty -s 'ispeed 9600 ospeed 9600' -l $BACKEND $FRONTEND | ./format_interceptty_output.sh
