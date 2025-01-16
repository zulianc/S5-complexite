# Charger les données depuis le fichier CSV
data <- read.csv("stats.csv", header = TRUE)

# Générer l'axe X (nombre d'éléments)
x <- seq(1, nrow(data))

# Extraire les colonnes pour insertion, recherche et suppression
insertion <- data[, 1]
search <- data[, 2]
deletion <- data[, 3]

# Tracer les courbes
plot(x,
    insertion,
    type = "l",
    col = "blue",
    lwd = 2,
    ylim = range(c(insertion, search, deletion)),
    xlab = "Number of elements",
    ylab = "Time (ms)",
    main = "AVL Tree Benchmark"
)
lines(x, search, col = "green", lwd = 2)
lines(x, deletion, col = "red", lwd = 2)

# Ajouter une légende
legend("topright", legend = c("Insertion", "Search", "Deletion"),
       col = c("blue", "green", "red"), lty = 1, lwd = 2)
