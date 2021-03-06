/* -*-C++-*- */
/*
 * Problem descriptions.
 *
 * Copyright (C) 2002-2004 Carnegie Mellon University
 * Written by H�kan L. S. Younes.
 *
 * Permission is hereby granted to distribute this software for
 * non-commercial research purposes, provided that this copyright
 * notice is included with any such distribution.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE
 * SOFTWARE IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU
 * ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.
 *
 * $Id: problems.h,v 6.8 2003-09-18 21:51:37 lorens Exp $
 */
#ifndef PROBLEMS_H
#define PROBLEMS_H

#include <config.h>
#include "domains.h"
#include "formulas.h"
#include "expressions.h"
#include "terms.h"
#include "types.h"


/* ====================================================================== */
/* TimedActionTable */

/*
 * A table of timed actions.
 */
struct TimedActionTable : public std::map<float, GroundAction*> {
};


/* ====================================================================== */
/* Problem */

/*
 * Problem definition.
 */
struct Problem {
  /* Table of problem definitions. */
  struct ProblemMap : public std::map<std::string, const Problem*> {
  };

  /* Returns a const_iterator pointing to the first problem. */
  static ProblemMap::const_iterator begin();

  /* Returns a const_iterator pointing beyond the last problem. */
  static ProblemMap::const_iterator end();

  /* Returns the problem with the given name, or NULL if it is undefined. */
  static const Problem* find(const std::string& name);

  /* Removes all defined problems. */
  static void clear();

  /* Constructs a problem. */
  Problem(const std::string& name, const Domain& domain);

  /* Deletes a problem. */
  ~Problem();

  /* Returns the name of this problem. */
  const std::string& name() const { return name_; }

  /* Returns the domain of this problem. */
  const Domain& domain() const { return *domain_; }

  /* Returns the term table of this problem. */
  TermTable& terms() { return terms_; }

  /* Returns the term table of this problem. */
  const TermTable& terms() const { return terms_; }

  /* Adds an atomic formula to the initial conditions of this problem. */
  void add_init_atom(const Atom& atom);

  /* Adds a timed initial literal to this problem. */
  void add_init_literal(float time, const Literal& literal);

  /* Adds a fluent value to the initial conditions of this problem. */
  void add_init_value(const Fluent& fluent, float value);

  /* Sets the goal of this problem. */
  void set_goal(const Formula& goal);

  /* Sets the metric to minimize for this problem. */
  void set_metric(const Expression& metric, bool negate = false);

  /* Returns the initial atoms of this problem. */
  const AtomSet& init_atoms() const { return init_atoms_; }

  /* Returns the initial values of this problem. */
  const ValueMap& init_values() const { return init_values_; }

  /* Returns the action representing the initial conditions of this problem. */
  const GroundAction& init_action() const { return init_action_; }

  /* Returns the actions representing the timed initial literals. */
  const TimedActionTable& timed_actions() const { return timed_actions_; }

  /* Returns the goal of this problem. */
  const Formula& goal() const { return *goal_; }

  /* Returns the metric to minimize for this problem. */
  const Expression& metric() const { return *metric_; }

  /* Tests if the metric is constant. */
  bool constant_metric() const;

  /* Fills the provided action list with ground actions instantiated
     from the action schemas of the domain. */
  void instantiated_actions(GroundActionList& actions) const;

private:
  /* Table of defined problems. */
  static ProblemMap problems;

  /* Name of problem. */
  std::string name_;
  /* Problem domain. */
  const Domain* domain_;
  /* Problem terms. */
  mutable TermTable terms_;
  /* Initial atoms. */
  AtomSet init_atoms_;
  /* Initial fluent values. */
  ValueMap init_values_;
  /* Aciton representing initial conditions of problem. */
  GroundAction init_action_;
  /* Actions representing timed initial conditions of problem. */
  TimedActionTable timed_actions_;
  /* Goal of problem. */
  const Formula* goal_;
  /* Metric to minimize. */
  const Expression* metric_;

  friend std::ostream& operator<<(std::ostream& os, const Problem& p);
};

/* Output operator for problems. */
std::ostream& operator<<(std::ostream& os, const Problem& p);


#endif /* PROBLEMS_H */
