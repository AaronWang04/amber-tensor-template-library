### Expression Templating
https://en.wikipedia.org/wiki/Expression_templates  
A template metapgramming technique used by Eigen (the numpy like library behind TensorFlow) that helps optimize performance of compiled code. It is a techniques that allows for the bypass of traditional order of evaluation and apply something called lazy evaluation. An example is when we write x = a + b + c, where b+c is first added, creating a new tempory class, which is then added to a and finally assigned to x. This results in two class instanciation when it could hav been one, and excess tempory memory is used in the middle of the computation. Expression templating uses recursive evaluation, and in the case of x = a + b + c, it would pass an expression for evaluating b+c to a, and then only when you assign a+b+c to x, does it fully evaluate the expression and assign the value to x. Since there are often updates to a tensor such as weights*value + bias, these types of optimization matter a lot. This is kind of a surface level explanation, but more can be found in the wikipedia page, it is well written. 

### More on cuda


