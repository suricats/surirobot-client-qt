/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   conf.hpp
 * Author: alain
 *
 * Created on 26 février 2018, 23:47
 */

#ifndef CONF_HPP
#define CONF_HPP

#define TMP_DIR "tmp/"
#define DEFAULT_LANGUAGE "fr"

//States

enum State {
    STATE_IDLE, STATE_DETECTED, STATE_WAITING_FOR_CONFIRMATION, STATE_CONFIRMATION_NO, STATE_CONFIRMATION_YES
};

#endif /* CONF_HPP */

