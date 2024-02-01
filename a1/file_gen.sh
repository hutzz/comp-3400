mkdir -p rundir
for ext in txt txT tXt tXT Txt TxT TXt TXT ; do \
       touch -t 202401151651 rundir/notokay.$ext ; \
       touch -t 202401261651 rundir/okay1.$ext ; \
       touch -t 202401261651 rundir/okay2.$ext ; \
       touch -t 202401281651 rundir/notokay.$ext ; \
done