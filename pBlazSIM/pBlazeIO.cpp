/*
 *  Copyright � 2003..2012 : Henk van Kampen <henk@mediatronix.com>
 *
 *  This file is part of pBlazASM.
 *
 *  pBlazASM is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  pBlazASM is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with pBlazASM.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QStandardItem>

#include "pBlaze.h"
#include "pBlazeIO.h"
#include "mainwindow.h"


// IO devices

// UART
uint32_t UART::getValue ( uint32_t address ) {
    if ( ( address & 1 ) == 0 )
        return ( (MainWindow *)w )->getUARTstatus() ;
    else
        return ( (MainWindow *)w )->getUARTdata() ;
}

void UART::setValue ( uint32_t address, uint32_t value ) {
    (void)address ;
    ((MainWindow *)w)->setUARTdata( value ) ;
}


// Cyclecounter CC
uint32_t CC::getValue(uint32_t address) {
    if ( ( address & 0x08 ) == 0 ) {
    uint64_t c = TimeStamp ;

        switch ( address & 0x07 ) {
        case 7 : c >>= 8 ;
        case 6 : c >>= 8 ;
        case 5 : c >>= 8 ;
        case 4 : c >>= 8 ;
        case 3 : c >>= 8 ;
        case 2 : c >>= 8 ;
        case 1 : c >>= 8 ;
        case 0 : ;
        }
        return c & 0xFF ;
    } else {
        uint64_t c = TimeDelta ;

        switch ( address & 0x07 ) {
        case 7 : c >>= 8 ;
        case 6 : c >>= 8 ;
        case 5 : c >>= 8 ;
        case 4 : c >>= 8 ;
        case 3 : c >>= 8 ;
        case 2 : c >>= 8 ;
        case 1 : c >>= 8 ;
        case 0 : ;
        }
        return c & 0xFF ;
    }
}

void CC::setValue(uint32_t address, uint32_t value) {
    (void)address ;
    (void)value ;

    if ( pBlaze != NULL ) {
        TimeDelta = pBlaze->CycleCounter - TimeStamp ;
        TimeStamp = pBlaze->CycleCounter ;
    }
}

// SBOX, for Rijndael
uint32_t SBOX::getValue(uint32_t address) {
    (void)address ;
    static const unsigned char SBox[256] = {
       0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
       0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
       0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
       0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
       0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
       0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
       0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
       0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
       0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
       0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
       0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
       0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
       0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
       0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
       0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
       0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
    } ;
    return SBox[ index & 0xFF ] ;
}

void SBOX::setValue( uint32_t address, uint32_t value ) {
    (void)address ;
    index = value ;
}

// LEDs
LEDs::LEDs() {
    greenIcon = new QIcon(":/images/bullet_ball_glass_red.png");
    blackIcon = new QIcon(":/images/bullet_ball_glass.png");

    rack = 0 ;
}

uint32_t LEDs::getValue(uint32_t address) {
    (void)address ;
    return rack ;
}

void LEDs::setValue(uint32_t address, uint32_t value ) {
    (void)address ;
    rack = value ;
}

void LEDs::update( void ) {
    for ( int bits = 0 ; bits < 8 ; bits += 1 )
        if ( leds[ bits ] != NULL ) {
            if ( ( ( rack >> bits ) & 1 ) != 0 )
                leds[ bits ]->setIcon( *greenIcon ) ;
            else
                leds[ bits ]->setIcon( *blackIcon ) ;
        }
}

void LEDs::setItem ( uint32_t reg, QStandardItem * item ) {
    leds[ reg ] = item ;
}


// SCRIPT
uint32_t SCRIPT::getValue(uint32_t address) {
    return ( (MainWindow *)w )->getScriptValue( address ) ;
}

void SCRIPT::setValue(uint32_t address, uint32_t value) {
    ( (MainWindow *)w )->setScriptValue( address, value ) ;
}


// QmtxPicoblaze

void QmtxPicoblaze::updateScratchPad( void ) {
    for ( int scr = 0 ; scr < MAXSCR ; scr += 1 ) {
        QStandardItem * item = (QStandardItem *)getScratchpadItem( scr ) ;
        if ( item != NULL ) {
            int n = getScratchpadValue( scr ) ;
            QString s = QString("%1").arg( n, 0, 16 ).toUpper() ;
            s = s.rightJustified( 2, '0' ) ;
            item->setData( s, Qt::DisplayRole ) ;
        }
    }
}

void QmtxPicoblaze::updateStack( void ) {
    QString s  ;

    for ( unsigned p = 0 ; p < MAXSTK ; p += 1 ) {
        QStandardItem * item = (QStandardItem *)getStackItem( p ) ;
        if ( item != NULL ) {
            s = "" ;
            if ( p < getSpValue() ) {
                int n = getStackPcValue( p ) ;
                s = QString("%1").arg( n, 0, 16 ).toUpper() ;
                s = s.rightJustified( 3, '0' ) ;
            }
            item->setData( s, Qt::DisplayRole ) ;
        }
    }
}

void QmtxPicoblaze::updateRegisters( void ) {
    QString s  ;

    for ( int reg = 0 ; reg < MAXREG ; reg += 1 ) {
        QStandardItem * item = (QStandardItem *)getRegisterItem( reg ) ;
        if ( item != NULL ) {
            s = "" ;
            if ( isRegisterDefined( reg ) ) {
                int n = getRegisterValue( reg ) ;
                s = QString("%1").arg( n, 0, 16 ).toUpper() ;
                s = s.rightJustified( 2, '0' ) ;
            }
            item->setData( s, Qt::DisplayRole ) ;
        }
    }
}

void QmtxPicoblaze::updateState( void ) {
    QStandardItem * item = (QStandardItem *)getStateItem( 0 ) ;
    QString s = QString("%1").arg( getPcValue(), 4 ) ;
    if ( item != NULL )
        item->setData( s, Qt::DisplayRole ) ;

    item = (QStandardItem *)getStateItem( 1 ) ;
    s = QString("%1").arg( getSpValue(), 4 ) ;
    if ( item != NULL )
        item->setData( s, Qt::DisplayRole ) ;

    item = (QStandardItem *)getStateItem( 2 ) ;
    s = QString("%1").arg( (int)getZero(), 4 ) ;
    if ( item != NULL )
        item->setData( s, Qt::DisplayRole ) ;

    item = (QStandardItem *)getStateItem( 3 ) ;
    s = QString("%1").arg( (int)getCarry(), 4 ) ;
    if ( item != NULL )
        item->setData( s, Qt::DisplayRole ) ;

    item = (QStandardItem *)getStateItem( 4 ) ;
    s = QString("%1").arg( (int)getEnable(), 4 ) ;
    if ( item != NULL )
        item->setData( s, Qt::DisplayRole ) ;

    item = (QStandardItem *)getStateItem( 5 ) ;
    s = getBank() == 0 ? "   A" : getBank() == 1 ? "   B" : "  ???" ;
    if ( item != NULL )
        item->setData( s, Qt::DisplayRole ) ;
}

void QmtxPicoblaze::updateIO( void )
{
    for ( int io = 0 ; io < MAXIO ; io += 1 )
        if ( getIODevice( io ) != NULL )
            getIODevice( io )->update();
}

void QmtxPicoblaze::updateData( void ) {
    updateScratchPad() ;
    updateStack() ;
    updateRegisters() ;
}

void QmtxPicoblaze::setScratchpadValue ( uint32_t cell, uint32_t value ) {
    Picoblaze::setScratchpadValue( cell, value ) ;

    QStandardItem * item = (QStandardItem *)getScratchpadItem( cell ) ;
    if ( item != NULL ) {
        QString s = QString("%1").arg( value, 0, 16 ).toUpper() ;
        s = s.rightJustified( 2, '0' ) ;
        item->setData( s, Qt::DisplayRole ) ;
    }
}

void QmtxPicoblaze::setRegisterValue ( uint32_t cell, uint32_t value ) {
    Picoblaze::setRegisterValue( cell, value ) ;

    QStandardItem * item = (QStandardItem *)getRegisterItem( cell ) ;
    if ( item != NULL ) {
        QString s = QString("%1").arg( value, 0, 16 ).toUpper() ;
        s = s.rightJustified( 2, '0' ) ;
        item->setData( s, Qt::DisplayRole ) ;
    }
}





