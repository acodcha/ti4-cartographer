#pragma once

#include "System.hpp"

namespace TI4Cartographer {

const std::unordered_set<System> Systems{
  { "1", GameVersion::BaseGame, SystemCategory::Home,
    {{"Jord", 4, 2, {}, {}, {}}}, {}, {}, {Faction::FederationOfSol}
  },
  { "2", GameVersion::BaseGame, SystemCategory::Home,
    {{"Moll Primus", 4, 1, {}, {}, {}}}, {}, {}, {Faction::MentakCoalition}
  },
  { "3", GameVersion::BaseGame, SystemCategory::Home,
    {{"Darien", 4, 4, {}, {}, {}}}, {}, {}, {Faction::YinBrotherhood}
  },
  { "4", GameVersion::BaseGame, SystemCategory::Home,
    {{"Muaat", 4, 1, {}, {}, {}}}, {}, {}, {Faction::EmbersOfMuaat}
  },
  { "5", GameVersion::BaseGame, SystemCategory::Home,
    {{"Nestphar", 3, 2, {}, {}, {}}}, {}, {}, {Faction::Arborec}
  },
  { "6", GameVersion::BaseGame, SystemCategory::Home,
    {{"[0.0.0]", 5, 0, {}, {}, {}}}, {}, {}, {Faction::L1z1xMindnet}
  },
  { "7", GameVersion::BaseGame, SystemCategory::Home,
    {{"Winnu", 3, 4, {}, {}, {}}}, {}, {}, {Faction::Winnu}
  },
  { "8", GameVersion::BaseGame, SystemCategory::Home,
    {{"Mordai II", 4, 0, {}, {}, {}}}, {}, {}, {Faction::NekroVirus}
  },
  { "9", GameVersion::BaseGame, SystemCategory::Home,
    { {"Druaa", 3, 1, {}, {}, {}},
      {"Maaluuk", 0, 2, {}, {}, {}}}, {}, {}, {Faction::NaaluCollective}
  },
  { "10", GameVersion::BaseGame, SystemCategory::Home,
    { {"Arc Prime", 4, 0, {}, {}, {}},
      {"Wren Terra", 2, 1, {}, {}, {}}}, {}, {}, {Faction::BaronyOfLetnev}
  },
  { "11", GameVersion::BaseGame, SystemCategory::Home,
    { {"Lisis II", 1, 0, {}, {}, {}},
      {"Ragh", 2, 1, {}, {}, {}}}, {}, {}, {Faction::ClanOfSaar}
  },
  { "12", GameVersion::BaseGame, SystemCategory::Home,
    { {"Jol", 1, 2, {}, {}, {}},
      {"Nar", 2, 3, {}, {}, {}}}, {}, {}, {Faction::UniversitiesOfJolNar}
  },
  { "13", GameVersion::BaseGame, SystemCategory::Home,
    { {"Quinarra", 3, 1, {}, {}, {}},
      {"Tren'lak", 1, 0, {}, {}, {}}}, {}, {}, {Faction::SardakkNorr}
  },
  { "14", GameVersion::BaseGame, SystemCategory::Home,
    { {"Archon Ren", 2, 3, {}, {}, {}},
      {"Archon Tau", 1, 1, {}, {}, {}}}, {}, {}, {Faction::XxchaKingdom}
  },
  { "15", GameVersion::BaseGame, SystemCategory::Home,
    { {"Retillion", 2, 3, {}, {}, {}},
      {"Shalloq", 1, 2, {}, {}, {}}}, {}, {}, {Faction::YssarilTribes}
  },
  { "16", GameVersion::BaseGame, SystemCategory::Home,
    { {"Arretze", 2, 0, {}, {}, {}},
      {"Hercant", 1, 1, {}, {}, {}},
      {"Kamdorn", 0, 1, {}, {}, {}}}, {}, {}, {Faction::EmiratesOfHacan}
  },
  { "17", GameVersion::BaseGame, SystemCategory::CreussGate,
    {}, {}, {Wormhole::Delta}, {Faction::GhostsOfCreuss}
  },
  { "18", GameVersion::BaseGame, SystemCategory::MecatolRex,
    {{"Mecatol Rex", 1, 6, {}, {}, {}}}, {}, {}
  },
  { "19", GameVersion::BaseGame, SystemCategory::Planetary,
    {{"Wellon", 1, 2, {TechnologyType::Cybernetic}, {PlanetTrait::Industrial}, {}}}, {}, {}
  },
  { "20", GameVersion::BaseGame, SystemCategory::Planetary,
    {{"Vefut II", 2, 2, {}, {PlanetTrait::Hazardous}, {}}}, {}, {}
  },
  { "21", GameVersion::BaseGame, SystemCategory::Planetary,
    {{"Thibah", 1, 1, {TechnologyType::Propulsion}, {PlanetTrait::Industrial}, {}}}, {}, {}
  },
  { "22", GameVersion::BaseGame, SystemCategory::Planetary,
    {{"Tar'mann", 1, 1, {TechnologyType::Biotic}, {PlanetTrait::Industrial}, {}}}, {}, {}
  },
  { "23", GameVersion::BaseGame, SystemCategory::Planetary,
    {{"Saudor", 2, 2, {}, {PlanetTrait::Industrial}, {}}}, {}, {}
  },
  { "24", GameVersion::BaseGame, SystemCategory::Planetary,
    {{"Mehar Xull", 1, 3, {TechnologyType::Warfare}, {PlanetTrait::Hazardous}, {}}}, {}, {}
  },
  { "25", GameVersion::BaseGame, SystemCategory::Planetary,
    {{"Quann", 2, 1, {}, {PlanetTrait::Cultural}, {}}},
    {}, {Wormhole::Beta}
  },
  { "26", GameVersion::BaseGame, SystemCategory::Planetary,
    {{"Lodor", 3, 1, {}, {PlanetTrait::Cultural}, {}}},
    {}, {Wormhole::Alpha}
  },
  { "27", GameVersion::BaseGame, SystemCategory::Planetary,
    { {"New Albion", 1, 1, {TechnologyType::Biotic}, {PlanetTrait::Industrial}, {}},
      {"Starpoint", 3, 1, {}, {PlanetTrait::Hazardous}, {}}
    }, {}, {}
  },
  { "28", GameVersion::BaseGame, SystemCategory::Planetary,
    { {"Tequ'ran", 2, 0, {}, {PlanetTrait::Hazardous}, {}},
      {"Torkan", 0, 3, {}, {PlanetTrait::Cultural}, {}}
    }, {}, {}
  },
  { "29", GameVersion::BaseGame, SystemCategory::Planetary,
    { {"Qucen'n", 1, 2, {}, {PlanetTrait::Industrial}, {}},
      {"Rarron", 0, 3, {}, {PlanetTrait::Cultural}, {}}
    }, {}, {}
  },
  { "30", GameVersion::BaseGame, SystemCategory::Planetary,
    { {"Mellon", 0, 2, {}, {PlanetTrait::Cultural}, {}},
      {"Zohbat", 3, 1, {}, {PlanetTrait::Hazardous}, {}}
    }, {}, {}
  },
  { "31", GameVersion::BaseGame, SystemCategory::Planetary,
    { {"Lazar", 1, 0, {TechnologyType::Cybernetic}, {PlanetTrait::Industrial}, {}},
      {"Sakulag", 2, 1, {}, {PlanetTrait::Hazardous}, {}}
    }, {}, {}
  },
  { "32", GameVersion::BaseGame, SystemCategory::Planetary,
    { {"Dal Bootha", 0, 2, {}, {PlanetTrait::Cultural}, {}},
      {"Xxehan", 1, 1, {}, {PlanetTrait::Cultural}, {}}
    }, {}, {}
  },
  { "33", GameVersion::BaseGame, SystemCategory::Planetary,
    { {"Corneeq", 1, 2, {}, {PlanetTrait::Cultural}, {}},
      {"Resculon", 2, 0, {}, {PlanetTrait::Cultural}, {}}
    }, {}, {}
  },
  { "34", GameVersion::BaseGame, SystemCategory::Planetary,
    { {"Centauri", 1, 3, {}, {PlanetTrait::Cultural}, {}},
      {"Gral", 1, 1, {TechnologyType::Propulsion}, {PlanetTrait::Industrial}, {}}
    }, {}, {}
  },
  { "35", GameVersion::BaseGame, SystemCategory::Planetary,
    { {"Bereg", 3, 1, {}, {PlanetTrait::Hazardous}, {}},
      {"Lirta IV", 2, 3, {}, {PlanetTrait::Hazardous}, {}}
    }, {}, {}
  },
  { "36", GameVersion::BaseGame, SystemCategory::Planetary,
    { {"Arnor", 2, 1, {}, {PlanetTrait::Industrial}, {}},
      {"Lor", 1, 2, {}, {PlanetTrait::Industrial}, {}}
    }, {}, {}
  },
  { "37", GameVersion::BaseGame, SystemCategory::Planetary,
    { {"Arinam", 1, 2, {}, {PlanetTrait::Industrial}, {}},
      {"Meer", 0, 4, {TechnologyType::Warfare}, {PlanetTrait::Hazardous}, {}}
    }, {}, {}
  },
  { "38", GameVersion::BaseGame, SystemCategory::Planetary,
    { {"Abyz", 3, 0, {}, {PlanetTrait::Hazardous}, {}},
      {"Fria", 2, 0, {}, {PlanetTrait::Hazardous}, {}}
    }, {}, {}
  },
  { "39", GameVersion::BaseGame, SystemCategory::AnomalyWormholeEmpty,
    {}, {}, {Wormhole::Alpha}
  },
  { "40", GameVersion::BaseGame, SystemCategory::AnomalyWormholeEmpty,
    {}, {}, {Wormhole::Beta}
  },
  { "41", GameVersion::BaseGame, SystemCategory::AnomalyWormholeEmpty,
    {}, {Anomaly::GravityRift}, {}
  },
  { "42", GameVersion::BaseGame, SystemCategory::AnomalyWormholeEmpty,
    {}, {Anomaly::Nebula}, {}
  },
  { "43", GameVersion::BaseGame, SystemCategory::AnomalyWormholeEmpty,
    {}, {Anomaly::Supernova}, {}
  },
  { "44", GameVersion::BaseGame, SystemCategory::AnomalyWormholeEmpty,
    {}, {Anomaly::AsteroidField}, {}
  },
  { "45", GameVersion::BaseGame, SystemCategory::AnomalyWormholeEmpty,
    {}, {Anomaly::AsteroidField}, {}
  },
  { "46", GameVersion::BaseGame, SystemCategory::AnomalyWormholeEmpty,
    {}, {}, {}
  },
  { "47", GameVersion::BaseGame, SystemCategory::AnomalyWormholeEmpty,
    {}, {}, {}
  },
  { "48", GameVersion::BaseGame, SystemCategory::AnomalyWormholeEmpty,
    {}, {}, {}
  },
  { "49", GameVersion::BaseGame, SystemCategory::AnomalyWormholeEmpty,
    {}, {}, {}
  },
  { "50", GameVersion::BaseGame, SystemCategory::AnomalyWormholeEmpty,
    {}, {}, {}
  },
  { "51", GameVersion::BaseGame, SystemCategory::Home,
    {{"Creuss", 4, 2, {}, {}, {}}}, {}, {Wormhole::Delta}, {Faction::GhostsOfCreuss}
  },
  { "52", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Home,
    {{"Ixth", 3, 5, {}, {}, {}}}, {}, {}, {Faction::MahactGeneSorcerers}
  },
  { "53", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Home,
    {{"Arcturus", 4, 4, {}, {}, {}}}, {}, {}, {Faction::Nomad}
  },
  { "54", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Home,
    {{"Acheron", 4, 0, {}, {}, {}}}, {}, {}, {Faction::VuilraithCabal}
  },
  { "55", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Home,
    {{"Elysium", 4, 1, {}, {}, {}}}, {}, {}, {Faction::TitansOfUl}
  },
  { "56", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Home,
    {{"The Dark", 3, 4, {}, {}, {}}}, {}, {}, {Faction::Empyrean}
  },
  { "57", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Home,
    { {"Naazir", 2, 1, {}, {}, {}},
      {"Rokha", 1, 2, {}, {}, {}}}, {}, {}, {Faction::NaazRokhaAlliance}
  },
  { "58", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Home,
    { {"Avar", 1, 1, {}, {}, {}},
      {"Valk", 2, 0, {}, {}, {}},
      {"Ylir", 0, 2, {}, {}, {}}}, {}, {}, {Faction::ArgentFlight}
  },
  { "59", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    {{"Archon Vail", 1, 3, {TechnologyType::Propulsion}, {PlanetTrait::Hazardous}, {}}}, {}, {}
  },
  { "60", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    {{"Perimeter", 2, 1, {}, {PlanetTrait::Industrial}, {}}}, {}, {}
  },
  { "61", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    {{"Ang", 2, 0, {TechnologyType::Warfare}, {PlanetTrait::Industrial}, {}}}, {}, {}
  },
  { "62", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    {{"Sem-Lore", 3, 2, {TechnologyType::Cybernetic}, {PlanetTrait::Cultural}, {}}}, {}, {}
  },
  { "63", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    {{"Vorhal", 0, 2, {TechnologyType::Biotic}, {PlanetTrait::Cultural}, {}}}, {}, {}
  },
  { "64", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    {{"Atlas", 3, 1, {}, {PlanetTrait::Hazardous}, {}}},
    {}, {Wormhole::Beta}
  },
  { "65", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    {{"Primor", 2, 1, {}, {PlanetTrait::Cultural}, {LegendaryPlanet::Primor}}},
    {}, {}
  },
  { "66", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    {{"Hope's End", 3, 0, {}, {PlanetTrait::Hazardous}, {LegendaryPlanet::HopesEnd}}},
    {}, {}
  },
  { "67", GameVersion::ProphecyOfKingsExpansion, SystemCategory::AnomalyWormholeEmpty,
    {{"Cormund", 2, 0, {}, {PlanetTrait::Hazardous}, {}}},
    {Anomaly::GravityRift}, {}
  },
  { "68", GameVersion::ProphecyOfKingsExpansion, SystemCategory::AnomalyWormholeEmpty,
    {{"Everra", 3, 1, {}, {PlanetTrait::Cultural}, {}}},
    {Anomaly::Nebula}, {}
  },
  { "69", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    { {"Accoen", 2, 3, {}, {PlanetTrait::Industrial}, {}},
      {"Jeol Ir", 2, 3, {}, {PlanetTrait::Industrial}, {}}}, {}, {}
  },
  { "70", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    { {"Kraag", 2, 1, {}, {PlanetTrait::Hazardous}, {}},
      {"Siig", 0, 2, {}, {PlanetTrait::Hazardous}, {}}}, {}, {}
  },
  { "71", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    { {"Ba'kal", 3, 2, {}, {PlanetTrait::Industrial}, {}},
      {"Alio Prima", 1, 1, {}, {PlanetTrait::Cultural}, {}}}, {}, {}
  },
  { "72", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    { {"Lisis", 2, 2, {}, {PlanetTrait::Industrial}, {}},
      {"Velnor", 2, 1, {TechnologyType::Warfare}, {PlanetTrait::Industrial}, {}}}, {}, {}
  },
  { "73", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    { {"Cealdri", 0, 2, {TechnologyType::Cybernetic}, {PlanetTrait::Cultural}, {}},
      {"Xanhact", 0, 1, {}, {PlanetTrait::Hazardous}, {}}}, {}, {}
  },
  { "74", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    { {"Vega Major", 2, 1, {}, {PlanetTrait::Cultural}, {}},
      {"Vega Minor", 1, 2, {TechnologyType::Propulsion}, {PlanetTrait::Cultural}, {}}}, {}, {}
  },
  { "75", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    { {"Abaddon", 1, 0, {}, {PlanetTrait::Cultural}, {}},
      {"Ashtroth", 2, 0, {}, {PlanetTrait::Hazardous}, {}},
      {"Loki", 1, 2, {}, {PlanetTrait::Cultural}, {}}}, {}, {}
  },
  { "76", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Planetary,
    { {"Rigel I", 0, 1, {}, {PlanetTrait::Hazardous}, {}},
      {"Rigel II", 1, 2, {}, {PlanetTrait::Industrial}, {}},
      {"Rigel III", 1, 1, {TechnologyType::Biotic}, {PlanetTrait::Industrial}, {}}}, {}, {}
  },
  { "77", GameVersion::ProphecyOfKingsExpansion, SystemCategory::AnomalyWormholeEmpty,
    {}, {}, {}
  },
  { "78", GameVersion::ProphecyOfKingsExpansion, SystemCategory::AnomalyWormholeEmpty,
    {}, {}, {}
  },
  { "79", GameVersion::ProphecyOfKingsExpansion, SystemCategory::AnomalyWormholeEmpty,
    {}, {Anomaly::AsteroidField}, {Wormhole::Alpha}
  },
  { "80", GameVersion::ProphecyOfKingsExpansion, SystemCategory::AnomalyWormholeEmpty,
    {}, {Anomaly::Supernova}, {}
  },
  { "82", GameVersion::ProphecyOfKingsExpansion, SystemCategory::WormholeNexus,
    {{"Mallice", 0, 3, {}, {PlanetTrait::Cultural}, {LegendaryPlanet::Mallice}}},
    {}, {Wormhole::Alpha, Wormhole::Beta, Wormhole::Gamma}
  },
  { "83A-0", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "83A-1", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "83A-2", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "83A-3", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "83A-4", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "83A-5", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "83B-0", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "83B-1", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "83B-2", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "83B-3", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "83B-4", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "83B-5", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "84A-0", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "84A-1", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "84A-2", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "84A-3", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "84A-4", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "84A-5", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "84B-0", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "84B-1", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "84B-2", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "84B-3", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "84B-4", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "84B-5", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "85A-0", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "85A-1", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "85A-2", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "85A-3", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "85A-4", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "85A-5", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "85B-0", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "85B-1", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "85B-2", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "85B-3", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "85B-4", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "85B-5", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "86A-0", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "86A-1", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "86A-2", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "86A-3", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "86A-4", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "86A-5", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "86B-0", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "86B-1", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "86B-2", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "86B-3", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "86B-4", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "86B-5", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "87A-0", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "87A-1", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "87A-2", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "87A-3", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "87A-4", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "87A-5", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "87B-0", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "87B-1", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "87B-2", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "87B-3", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "87B-4", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "87B-5", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "88A-0", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "88A-1", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "88A-2", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "88A-3", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "88A-4", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "88A-5", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "88B-0", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "88B-1", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "88B-2", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "88B-3", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "88B-4", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "88B-5", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "89A-0", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "89A-1", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "89A-2", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "89A-3", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "89A-4", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "89A-5", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "89B-0", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "89B-1", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "89B-2", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "89B-3", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "89B-4", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "89B-5", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "90A-0", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "90A-1", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "90A-2", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "90A-3", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "90A-4", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "90A-5", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "90B-0", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "90B-1", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "90B-2", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "90B-3", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "90B-4", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "90B-5", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "91A-0", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "91A-1", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "91A-2", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "91A-3", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "91A-4", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "91A-5", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "91B-0", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "91B-1", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "91B-2", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "91B-3", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "91B-4", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}},
  { "91B-5", GameVersion::ProphecyOfKingsExpansion, SystemCategory::Hyperlane, {}, {}, {}}
};

} // namespace TI4Cartographer
