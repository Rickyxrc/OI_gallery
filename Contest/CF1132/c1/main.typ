#import "../../../lib.typ": *

#let contest-id = "CF1132"
#let problem-id = "c1"
#let title = "Disgusting + GCD (Constructive Version)"

#let statement = include problem-id + ".prob.typ"
#let solution = include problem-id + ".sol.typ"

#let content_ = title_ => make-problem(
  contest-id: contest-id,
  problem-id: problem-id,
  title: title_,
  statement: statement,
  solution: solution,
)
#let content = content_(upper(problem-id) + "." + title)

#show: article

#content_(contest-id + " " + upper(problem-id) + "." + title)()
