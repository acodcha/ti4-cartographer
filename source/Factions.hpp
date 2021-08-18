#pragma once

#include "Base.hpp"

namespace TI4Cartographer {

enum class Faction : uint8_t {
  FederationOfSol,
  MentakCoalition,
  YinBrotherhood,
  EmbersOfMuaat,
  Arborec,
  L1z1xMindnet,
  Winnu,
  NekroVirus,
  NaaluCollective,
  BaronyOfLetnev,
  ClanOfSaar,
  UniversitiesOfJolNar,
  SardakkNorr,
  XxchaKingdom,
  YssarilTribes,
  EmiratesOfHacan,
  GhostsOfCreuss,
  MahactGeneSorcerers,
  Nomad,
  VuilraithCabal,
  TitansOfUl,
  Empyrean,
  NaazRokhaAlliance,
  ArgentFlight
};

template <> const std::unordered_map<Faction, std::string> labels<Faction>{
  {Faction::FederationOfSol, "Federation of Sol"},
  {Faction::MentakCoalition, "Mentak Coalition"},
  {Faction::YinBrotherhood, "Yin Brotherhood"},
  {Faction::EmbersOfMuaat, "Embers of Muaat"},
  {Faction::Arborec, "Arborec"},
  {Faction::L1z1xMindnet, "L1z1x Mindnet"},
  {Faction::Winnu, "Winnu"},
  {Faction::NekroVirus, "Nekro Virus"},
  {Faction::NaaluCollective, "Naalu Collective"},
  {Faction::BaronyOfLetnev, "Barony of Letnev"},
  {Faction::ClanOfSaar, "Clan of Saar"},
  {Faction::UniversitiesOfJolNar, "Universities of Jol-Nar"},
  {Faction::SardakkNorr, "Sardakk N'orr"},
  {Faction::XxchaKingdom, "Xxcha Kingdom"},
  {Faction::YssarilTribes, "Yssaril Tribes"},
  {Faction::EmiratesOfHacan, "Emirates of Hacan"},
  {Faction::GhostsOfCreuss, "Ghosts of Creuss"},
  {Faction::MahactGeneSorcerers, "Mahact Gene-Sorcerers"},
  {Faction::Nomad, "Nomad"},
  {Faction::VuilraithCabal, "Vuil'raith Cabal"},
  {Faction::TitansOfUl, "Titans of Ul"},
  {Faction::Empyrean, "Empyrean"},
  {Faction::NaazRokhaAlliance, "Naaz-Rokha Alliance"},
  {Faction::ArgentFlight, "Argent Flight"}
};

template <> const std::unordered_map<std::string, Faction> spellings<Faction>{
  {"federationofsol", Faction::FederationOfSol},
  {"mentakcoalition", Faction::MentakCoalition},
  {"yinbrotherhood", Faction::YinBrotherhood},
  {"embersofmuaat", Faction::EmbersOfMuaat},
  {"arborec", Faction::Arborec},
  {"l1z1xmindnet", Faction::L1z1xMindnet},
  {"winnu", Faction::Winnu},
  {"nekrovirus", Faction::NekroVirus},
  {"naalucollective", Faction::NaaluCollective},
  {"baronyofletnev", Faction::BaronyOfLetnev},
  {"clanofsaar", Faction::ClanOfSaar},
  {"universitiesofjolnar", Faction::UniversitiesOfJolNar},
  {"sardakknorr", Faction::SardakkNorr},
  {"xxchakingdom", Faction::XxchaKingdom},
  {"yssariltribes", Faction::YssarilTribes},
  {"emiratesofhacan", Faction::EmiratesOfHacan},
  {"ghostsofcreuss", Faction::GhostsOfCreuss},
  {"mahactgenesorcerers", Faction::MahactGeneSorcerers},
  {"nomad", Faction::Nomad},
  {"vuilraithcabal", Faction::VuilraithCabal},
  {"titansoful", Faction::TitansOfUl},
  {"empyrean", Faction::Empyrean},
  {"naazrokhaalliance", Faction::NaazRokhaAlliance},
  {"argentflight", Faction::ArgentFlight}
};

const std::unordered_map<Faction, uint8_t> factions_to_home_system_ids{
  {Faction::FederationOfSol, 1},
  {Faction::MentakCoalition, 2},
  {Faction::YinBrotherhood, 3},
  {Faction::EmbersOfMuaat, 4},
  {Faction::Arborec, 5},
  {Faction::L1z1xMindnet, 6},
  {Faction::Winnu, 7},
  {Faction::NekroVirus, 8},
  {Faction::NaaluCollective, 9},
  {Faction::BaronyOfLetnev, 10},
  {Faction::ClanOfSaar, 11},
  {Faction::UniversitiesOfJolNar, 12},
  {Faction::SardakkNorr, 13},
  {Faction::XxchaKingdom, 14},
  {Faction::YssarilTribes, 15},
  {Faction::EmiratesOfHacan, 16},
  {Faction::GhostsOfCreuss, 51},
  {Faction::MahactGeneSorcerers, 52},
  {Faction::Nomad, 53},
  {Faction::VuilraithCabal, 54},
  {Faction::TitansOfUl, 55},
  {Faction::Empyrean, 56},
  {Faction::NaazRokhaAlliance, 57},
  {Faction::ArgentFlight, 58}
};

uint8_t home_system_id(const Faction faction) noexcept {
  const std::unordered_map<Faction, uint8_t>::const_iterator found{factions_to_home_system_ids.find(faction)};
  if (found != factions_to_home_system_ids.cend()) {
    return found->second;
  }
  return 0;
}

const std::unordered_map<uint8_t, Faction> home_system_ids_to_factions{
  {1, Faction::FederationOfSol},
  {2, Faction::MentakCoalition},
  {3, Faction::YinBrotherhood},
  {4, Faction::EmbersOfMuaat},
  {5, Faction::Arborec},
  {6, Faction::L1z1xMindnet},
  {7, Faction::Winnu},
  {8, Faction::NekroVirus},
  {9, Faction::NaaluCollective},
  {10, Faction::BaronyOfLetnev},
  {11, Faction::ClanOfSaar},
  {12, Faction::UniversitiesOfJolNar},
  {13, Faction::SardakkNorr},
  {14, Faction::XxchaKingdom},
  {15, Faction::YssarilTribes},
  {16, Faction::EmiratesOfHacan},
  {51, Faction::GhostsOfCreuss},
  {52, Faction::MahactGeneSorcerers},
  {53, Faction::Nomad},
  {54, Faction::VuilraithCabal},
  {55, Faction::TitansOfUl},
  {56, Faction::Empyrean},
  {57, Faction::NaazRokhaAlliance},
  {58, Faction::ArgentFlight}
};

std::optional<Faction> home_system_id(const uint8_t home_system_id) noexcept {
  const std::unordered_map<uint8_t, Faction>::const_iterator found{home_system_ids_to_factions.find(home_system_id)};
  if (found != home_system_ids_to_factions.cend()) {
    return found->second;
  }
  const std::optional<Faction> no_data;
  return no_data;
}

} // namespace TI4Cartographer
