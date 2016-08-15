hdata <- read.csv('hepatitis.csv')
hdata[is.na(hdata[,15]),15] = mean(hdata[,15],na.rm = TRUE)
hdata[is.na(hdata[,16]),16] = as.integer(mean(hdata[,16],na.rm = TRUE))
hdata[is.na(hdata[,17]),17] = as.integer(mean(hdata[,17],na.rm = TRUE))
hdata[is.na(hdata[,18]),18] = mean(hdata[,18],na.rm = TRUE)
hdata[is.na(hdata[,19]),19] = as.integer(mean(hdata[,19],na.rm = TRUE))
write.csv(hdata,'hepatitis_mean.csv')

hdata <- read.csv('hepatitis.csv')
hdata[is.na(hdata[,15]),15] = median(hdata[,15],na.rm = TRUE)
hdata[is.na(hdata[,16]),16] = median(hdata[,16],na.rm = TRUE)
hdata[is.na(hdata[,17]),17] = median(hdata[,17],na.rm = TRUE)
hdata[is.na(hdata[,18]),18] = median(hdata[,18],na.rm = TRUE)
hdata[is.na(hdata[,19]),19] = median(hdata[,19],na.rm = TRUE)
write.csv(hdata,'hepatitis_median.csv')

hdata <- read.csv('hepatitis.csv')
hdata[is.na(hdata[,15]),15] = min(hdata[,15],na.rm = TRUE)
hdata[is.na(hdata[,16]),16] = min(hdata[,16],na.rm = TRUE)
hdata[is.na(hdata[,17]),17] = min(hdata[,17],na.rm = TRUE)
hdata[is.na(hdata[,18]),18] = min(hdata[,18],na.rm = TRUE)
hdata[is.na(hdata[,19]),19] = min(hdata[,19],na.rm = TRUE)
write.csv(hdata,'hepatitis_min.csv')

hdata <- read.csv('hepatitis.csv')
hdata[is.na(hdata[,15]),15] = max(hdata[,15],na.rm = TRUE)
hdata[is.na(hdata[,16]),16] = max(hdata[,16],na.rm = TRUE)
hdata[is.na(hdata[,17]),17] = max(hdata[,17],na.rm = TRUE)
hdata[is.na(hdata[,18]),18] = max(hdata[,18],na.rm = TRUE)
hdata[is.na(hdata[,19]),19] = max(hdata[,19],na.rm = TRUE)
write.csv(hdata,'hepatitis_max.csv')

getmode <- function(v) {
  uniqv <- unique(v)
  uniqv[which.max(tabulate(match(v, uniqv)))]
}

hdata <- read.csv('hepatitis.csv')
hdata[is.na(hdata[,16]),16] = getmode(hdata[!is.na(hdata[,16]),16])
hdata[is.na(hdata[,17]),17] = getmode(hdata[!is.na(hdata[,17]),17])
hdata[is.na(hdata[,19]),19] = getmode(hdata[!is.na(hdata[,19]),19])
write.csv(hdata,'hepatitis_mode.csv')