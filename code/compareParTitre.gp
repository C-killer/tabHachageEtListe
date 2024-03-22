# 输入文件路径
datafile1 = "tempsParTitreLC.txt"
datafile2 = "tempsParTitreH10000.txt"
datafile3 = "tempsParTitreH12500.txt"
datafile4 = "tempsParTitreH15000.txt"
datafile5 = "tempsParTitreH17500.txt"
datafile6 = "tempsParTitreH20000.txt"

# 设置绘图选项
set title "Comparaison du Programme (Titre) "
set xlabel "Nombre de Livres à Rechercher"
set ylabel "Temps (secondes)"
set grid

# 绘制图像
plot datafile1 using 1:2 with linespoints title "Temps de la  Liste Chaînée", \
     datafile2 using 1:2 with linespoints title "Temps de la Table de Hachage (taille = 10000)", \
     datafile3 using 1:2 with linespoints title "Temps de la Table de Hachage (taille = 12500)", \
     datafile4 using 1:2 with linespoints title "Temps de la Table de Hachage (taille = 15000)", \
     datafile5 using 1:2 with linespoints title "Temps de la Table de Hachage (taille = 17500)", \
     datafile6 using 1:2 with linespoints title "Temps de la Table de Hachage (taille = 20000)"

