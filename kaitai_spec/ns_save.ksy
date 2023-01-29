meta:
  id: ns
  file-extension: ns
  endian: be
seq:
  - id: file_format_version_tag
    type: s4
  - id: name_len_tag
    type: s4
  - id: name_tag
    type: str
    size: name_len_tag
    encoding: ASCII
  - id: player_hp_tag
    type: s4
  - id: player_max_hp_tag
    type: s4  
  - id: player_exp_cl_tag
    type: s4  
  - id: player_exp_ml_tag
    type: s4
  - id: player_call_level_skill_tag
    type: s4    
  - id: player_mechanics_level_skill_tag
    type: s4
  - id: player_money_tag
    type: s4
  - id: player_read_necronomicon_tag
    type: s4
  - id: player_has_unit_tag
    type: s4
  - id: unit_hp_tag
    type: s4
    if: player_has_unit_tag == 1  
  - id: unit_max_hp_tag
    type: s4
    if: player_has_unit_tag == 1  
  - id: unit_danger_level_tag
    type: s4
    if: player_has_unit_tag == 1  
  - id: unit_damage_tag
    type: s4
    if: player_has_unit_tag == 1  
  - id: unit_armour_tag
    type: s4
    if: player_has_unit_tag == 1  
  - id: unit_plazma_tag
    type: s4
    if: player_has_unit_tag == 1  
  - id: unit_gun_tag
    type: s4
    if: player_has_unit_tag == 1  
  - id: unit_neirosynaptic_tag
    type: s4
    if: player_has_unit_tag == 1  