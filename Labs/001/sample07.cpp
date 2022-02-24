#include <set>
#include <iostream>
#include <gmsh.h>

int main(int argc, char **argv)
{
  gmsh::initialize();

  gmsh::model::add("t7");

  gmsh::logger::start();

  double lc = 1e-4;

  //gmsh::model::occ::addBox(0, 0, 0, 1, 1, 1, 1);
  //gmsh::model::occ::addBox(0, 0, 0, 0.5, 0.5, 0.5, 2);

  gmsh::model::occ::addTorus(5., 5., 5., 1.4, 0.6, 1);
  gmsh::model::occ::addTorus(5., 5., 5., 1.4, 0.4, 2);

  std::vector<std::pair<int, int>> v2;
  std::vector<std::vector<std::pair<int, int>>> ovv;
  gmsh::model::occ::cut({{3, 1}}, {{3, 2}}, v2, ovv, 3);
  
  
  gmsh::model::occ::synchronize();

  gmsh::model::mesh::generate(3);

  gmsh::write("t7.msh");

  std::set<std::string> args(argv, argv + argc);
  if(!args.count("-nopopup")) gmsh::fltk::run();

  gmsh::finalize();

  return 0;
}
