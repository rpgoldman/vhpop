(define (problem uget-paid)
  (:domain uni-bw)
  (:objects home p d office)
  (:init (at b home) (at p home) (at d home) (in p))
  (:goal (and (at b office) (at d office) (at p home))))