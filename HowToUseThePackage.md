# Short Howto #

This is in no way replacing the tutorial files. This is just a quick start for the package.

There are two folders in the package and they have the source for Regression and Classification based Random Forests. Just add both to your path and you should be fine. And also everything was installed (like the compilation etc)

Lets say your data is in X\_trn and labels/target values are in Y\_trn. Make sure both of these are in doubles.

Simply Y\_trn = double(Y\_trn) and X\_trn = double(X\_trn) if you are not sure.


Creating Models
> regression: model\_reg = regRF\_train(X\_trn,Y\_trn);

> classification: model\_class = classRF\_train(X\_trn,Y\_trn);


Testing Models
We created model\_reg and model\_class in previous steps. Both are simply matlab variables that you can save, load, etc.



Testing/ Predicting for new data:
Let's say the data to predict is X\_tst and Y\_tst

regression: Y\_hat = regRF\_predict(X\_tst,model);
> err\_rate = (Y\_hat-Y\_tst)^2 %mse
classification: Y\_hat = classRF\_predict(X\_tst,model);
> err\_rate = length(find(Y\_hat~=Y\_tst)) %number of misclassification