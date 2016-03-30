# So you got things running, now getting better accuracy #

Assume, N=number of examples, D=number of features

For Large D and low N,

**Start with default mtry, mtry = sqrt(D) for classification, and mtry = D/3 for regression.**

Noisy Dataset: accuracy will be dictated by the signal to noise ratio, as RF samples mtry features at each point, if there are too many noisy features then there is a possibility that noisy features will be resampled many times and the error rate will be higher.

Solution: parameterically search between D/10: D/10: D and also include sqrt(D). Use about 1000 trees and choose the forest with the lowest out of bag error


**Importance?  personally imho, the best importance is the importance obtained from the best performing model.**


**How many trees are really required? personally, 1000 trees are most required (for most datasets i dealt with and after finding the ideal mtry). A way to find the ideal number of trees is to plot the out of bag error rate and choose a tree value after which out of bag error stabilizes.**

