# Homework
* filelog
  * Homework7.pdf
  * Genetic Algorithm.cpp
  * cout result.txt
* implementation details in Genetic Algorithm
  * preparation before start:I choose 10 as the individuals in the group,and each individuals have their chromosomes,x,fx and fitness.
  * about chromosomes: I choose the criterion like floats,and the first chromosome represents 8 or 0,the second represents 4 or 0...;so we can represent all x in the Domain(0~16)(why not -1~15?,cause I add a tmp(0~16) = x(-1~15) + 1).With such method,we can get result more accurately.
  * stopping criterion:I consider that the premise of problem is we don't know the x ,so we don't have some methods to analyze whether the individuals are optimal
  ,so I use the loop as the stopping criterion.In the print example, I chose 50 as the number of loops.
  *  the reproduction method:In this fuction,I add a reproductionrate as a simulation of nature,I choose the individuals who want to be a parent as parents.Then I divide
  them in several pairs,then begin crossover method.After I do a selection to make sure the number of individuals in the group stable.
     * the crossover method: In the crossover process,the parents crossover by two-point crossover.
     * the selection method: we use selectionflag as the flag of whether the individuals are disused.And we will continue the selection until the groupnum = 10.And the selection is aboout the fx(xsinx),but we can easily know that if we use it as weight directly,we may get a weight negative.So i choose the exp(fx) as the weight(propability).It solves that problem and we can find that we make the gap bigger between two numbers in big differece.
  * the mutation method: The mutation method I choose the random number as the criterion of whether the mutation happens.
  * the Test performance：I test the code many times and I find the results have something in common-- the result quickly converges but can't have higher accuracy.I analyze it and think the reason is about the exp.The exp function can have a larger gap if two numbers are in big difference,but when the accuracy become higher,the exp fuction may have the pposite effect.
      
     
