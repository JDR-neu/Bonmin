// (C) Copyright International Business Machines Corporation 2007
// All Rights Reserved.
// This code is published under the Common Public License.
//
// Authors :
// Pierre Bonami, International Business Machines Corporation
//
// Date : 04/12/2007

#ifndef BabSetupBase_H
#define BabSetupBase_H

#include <string>
#include <list>
#include "CglCutGenerator.hpp"
#include "CbcHeuristic.hpp"
#include "OsiChooseVariable.hpp"
#include "BonOsiTMINLPInterface.hpp"
namespace Bonmin{
  /** A class to have all elements necessary to setup a branch-and-bound.*/
  class BabSetupBase {
public:
    /** Type for cut generation method with its frequency and string identification. */
    struct CuttingMethod{
      int frequency;
      std::string id;
      CglCutGenerator * cgl;
      bool atSolution;
      CuttingMethod():
      atSolution(false){
      }
      CuttingMethod(const CuttingMethod & other):
        frequency(other.frequency),
        id(other.id),
        cgl(other.cgl),
        atSolution(other.atSolution)
      {}
    };
    typedef std::list<CuttingMethod> CuttingMethods;
    typedef std::list<CbcHeuristic * > HeuristicMethods;
    
    /** Default strategies for processing next node. */
    enum NodeSelectionStrategy {
      bestBound = 0 /** Best bound*/,
      DFS /** Depth First Search*/,
      BFS /** Best First Search */,
      dynamic /** Dynamic strategy, see <a href="http://www.coin-or.org/Doxygen/Cbc/class_cbc_branch_dynamic_decision.html">
		  CbcBranchActual.hpp </a> for explanations.*/,
      bestGuess /** Best guessed integer solution is subtree below, based on pseudo costs */
      };
     
    /** Parameters represented by an integer. */
    enum IntParameter{
      BabLogLevel = 0 /** Log level of main branch-and-bound*/,
      BabLogInterval/** Display information every logIntervval nodes.*/,
      MaxFailures /** Max number of failures in a branch.*/,
      FailureBehavior /** Behavior of the algorithm in the case of a failure.*/,
      MaxInfeasible /** Max number of consecutive infeasible problem in a branch
      before fathoming.*/,
      NumberStrong /** Number of candidates for strong branching.*/,
      MinReliability /** Minimum reliability before trust pseudo-costs.*/,
      MaxNodes /** Global node limit.*/,
      MaxSolutions /** limit on number of integer feasible solution.*/,
      MaxIterations /** Global iteration limit. */,
      SpecialOption /** Spetial option in particular for Cbc. */,
      DisableSos /** Consider or not SOS constraints.*/,
      NumCutPasses/** Number of cut passes at nodes.*/,
      NumberIntParam /** Dummy end to size table*/
    };

    
    /** Parameters represented by a double.*/
    enum DoubleParameter{
      CutoffDecr = 0 /** Amount by which cutoff is incremented */,
      Cutoff /** cutoff value */,
      AllowableGap /** Stop if absolute gap is less than this. */,
      AllowableFractionGap /** Stop if relative gap is less than this.*/,
      IntTol /** Integer tolerance.*/,
      MaxTime /** Global time limit. */,
      NumberDoubleParam /** Dummy end to size table*/
    };
    
    /** Default constructor. */
    BabSetupBase();
    
    /** Construct from existing tminlp. */
    BabSetupBase(Ipopt::SmartPtr<TMINLP> tminlp);
    /** Construct from existing application.*/
    BabSetupBase(Ipopt::SmartPtr<TNLPSolver> app);
    /** Construct from existing TMINLP interface.*/
    BabSetupBase(const OsiTMINLPInterface& nlp);


    /** Copy constructor. */
    BabSetupBase(const BabSetupBase & other);
    
    /** virtual copy constructor. */
    virtual BabSetupBase * clone() const = 0;
    
    /** Virtual destructor. */
    virtual ~BabSetupBase();
    
    /** @name Methods to initialize algorithm with various inputs. */
    /** @{ */
    /** use existing TMINLP interface (containing the options).*/
    void use(const OsiTMINLPInterface& nlp);
    /** Read options (if not done before) and create interface using tminlp.*/
    void use(Ipopt::SmartPtr<TMINLP> tminlp );
    /** Set the non-linear solver used */
    void setNonlinearSolver(OsiTMINLPInterface * s){
      nonlinearSolver_ = s;}
    /** @} */

    /** @name Methods to manipulate options. */
    /** @{ */
    /** Register all the options for this algorithm instance.*/
    virtual void registerOptions();
    /** Setup the defaults options for this algorithm. */
    virtual void setBabDefaultOptions(Ipopt::SmartPtr<Ipopt::RegisteredOptions> roptions) {}
    /** Register all the options for this algorithm instance.*/
    static void registerAllOptions(Ipopt::SmartPtr<Ipopt::RegisteredOptions> roptions);

    /** Get the options from default text file (bonmin.opt) if don't already have them.*/
    virtual void readOptionsFile(){
      if(readOptions_) return;
      readOptionsFile("bonmin.opt");}
    
    /** Get the options from given fileName */
      void readOptionsFile(std::string fileName);
    
    /** Get the options from long string containing all.*/
    void readOptionsString(std::string opt_string);
    
    /** Get the options from stream.*/
    void readOptionsStream(std::istream& is);
    
    /** May print documentation of options if options print_options_documentation is set to yes.*/
    void mayPrintDoc();
    

    /** Set the value for options, output...*/
    void setOptionsAndJournalist(Ipopt::SmartPtr<Ipopt::RegisteredOptions> roptions,
                                 Ipopt::SmartPtr<Ipopt::OptionsList> options,
                                 Ipopt::SmartPtr<Ipopt::Journalist> journalist){
      options_ = options;
      roptions_ = roptions;
      journalist_ = journalist;}
    
    /** Initialize the options and the journalist.*/
    void initializeOptionsAndJournalist();
    /** @} */
    
    /** @name Elements of the branch-and-bound setup.*/
    /** @{ */
    /** Pointer to the non-linear solver used.*/
    OsiTMINLPInterface * nonlinearSolver()
    {return nonlinearSolver_;}
    /** Pointer to the continuous solver to use for relaxations. */
    OsiSolverInterface * continuousSolver()
    { return continuousSolver_;}
    /** list of cutting planes methods to apply with their frequencies. */
    CuttingMethods& cutGenerators()
    { return cutGenerators_;}
    /** list of Heuristic methods to use. */
    HeuristicMethods& heuristics()
    { return heuristics_;}
    /** branching method to use. */
    OsiChooseVariable * branchingMethod()
    { return branchingMethod_;}
    /** Node selection strategy. */
    NodeSelectionStrategy nodeSelectionMethod()
    {return nodeSelectionMethod_;}
    /** Return value of integer parameter. */
    int getIntParameter(const IntParameter &p)
    {return intParam_[p];}
    /** Return value of double parameter.*/
    double getDoubleParameter(const DoubleParameter &p)
    {return doubleParam_[p];}
    /** @} */
    
    /** Get the values of base parameters from the options stored.*/
    void gatherParametersValues(){
      gatherParametersValues(options_);
    }
    /** Get the values of the base parameters from the passed options.*/
    void gatherParametersValues(Ipopt::SmartPtr<OptionsList> options);
    /** Acces storage of Journalist for output */
    Ipopt::SmartPtr<Ipopt::Journalist> journalist(){ return journalist_;}
    
    /** Acces list of Options */
    Ipopt::SmartPtr<Ipopt::OptionsList> options(){return options_;}
    
    /** Access registered Options */
    Ipopt::SmartPtr<Ipopt::RegisteredOptions> roptions(){return roptions_;}
    
protected:
    /** storage of integer parameters.*/
    int intParam_[NumberIntParam];
    /** default values for int parameters.*/
    static int defaultIntParam_[NumberIntParam];
    /** storage of double parameters. */
    double doubleParam_[NumberDoubleParam];
    /** default values for double parameters. */
    static double defaultDoubleParam_[NumberDoubleParam];
    /** Storage of the non-linear solver used.*/
    OsiTMINLPInterface * nonlinearSolver_;
    /** Storage of continuous solver.*/
    OsiSolverInterface * continuousSolver_;
    /** Cut generation methods. */
    CuttingMethods cutGenerators_;
    /** Heuristic methods. */
    HeuristicMethods heuristics_;
    /** Branching method.*/
    OsiChooseVariable * branchingMethod_;
    /** Node selection method.*/
    NodeSelectionStrategy nodeSelectionMethod_;
    
    /** Storage of Journalist for output */
    Ipopt::SmartPtr<Ipopt::Journalist> journalist_;
    
    /** List of Options */
    Ipopt::SmartPtr<Ipopt::OptionsList> options_;
    
    /** Registered Options */
    Ipopt::SmartPtr<Ipopt::RegisteredOptions> roptions_;
    /** flag to say if option file was read.*/
    bool readOptions_;
    /** separate message handler if continuousSolver_!= nonlinearSolver.*/
    CoinMessageHandler * lpMessageHandler_;
  };
}/* End namespace Bonmin. */
#endif
