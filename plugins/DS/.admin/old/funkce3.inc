<?php
function create_part_array($structure, $prefix="") {
   $part_array = array();

    if (sizeof($structure->parts) > 0) {
        foreach ($structure->parts as $count => $part) {
            add_part_to_array($part, $prefix.($count+1), $part_array);
        }
    }
   
   return $part_array;
}

function add_part_to_array($obj, $partno, & $part_array) {

    if ($obj->type == TYPEMESSAGE) {
        parse_message($obj->parts[0], $partno.".");
    }
    else {
        if (sizeof($obj->parts) > 0) {
            foreach ($obj->parts as $count => $p) {
                add_part_to_array($p, $partno.".".($count+1), $part_array);
            }
        }
    }
   
    $part_array[] = array('part_number' => $partno, 'part_object' => $obj);
}