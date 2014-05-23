mkdir dos
mkdir dos/examples
mkdir dos/4pp
mkdir dos/4pp/lib
mkdir dos/apps
mkdir dos/apps/basic
mkdir dos/apps/bf
mkdir dos/apps/data
mkdir dos/apps/graphics
mkdir dos/apps/markov
mkdir dos/apps/opg
mkdir dos/apps/tinyc
mkdir dos/apps/wirewrld
mkdir dos/bench
mkdir dos/demo
mkdir dos/lib

for file in `ls *.4th`
  do duc -d $file dos/examples/$file
done

cp *.scr dos/examples
duc -d Makefile dos/examples/Makefile

cd 4pp
for file in `ls *.4pp`
  do duc -d $file ../dos/4pp/$file
done

cd lib
for file in `ls *.4pp`
  do duc -d $file ../../dos/4pp/lib/$file
done

cd ../../bench
for file in `ls *.4th`
  do duc -d $file ../dos/bench/$file
done

cd ../demo
for file in `ls *.4th`
  do duc -d $file ../dos/demo/$file
done

cd ../lib
for file in `ls *.4th`
  do duc -d $file ../dos/lib/$file
done

cd ../apps/basic
for file in `ls *.bas`
  do duc -d $file ../../dos/apps/basic/$file
done

cd ../graphics
for file in `ls *.txt`
  do duc -d $file ../../dos/apps/graphics/$file
done

cp *.ppm ../../dos/apps/graphics

cd ../bf
for file in `ls *.b`
  do duc -d $file ../../dos/apps/bf/$file
done

cd ../data
cp * ../../dos/apps/data

cd ../markov
for file in `ls *.mrk`
  do duc -d $file ../../dos/apps/markov/$file
done

cd ../opg
for file in `ls *.opg`
  do duc -d $file ../../dos/apps/opg/$file
done


cd ../tinyc
for file in `ls *.tc`
  do duc -d $file ../../dos/apps/tinyc/$file
done

cd ../wirewrld
for file in `ls *.ww`
  do duc -d $file ../../dos/apps/wirewrld/$file
done

cd ../..