(define (problem uget-paid2)
  (:domain uni-bw)
  (:objects home office p d)
  (:init (place home) (place office) (object p) (object d) (object b)
	 (at b home) (at p home) (at d home) (in p))
  (:goal (and (at p home) (at d office) (at b home))))