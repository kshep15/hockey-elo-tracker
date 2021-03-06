package com.hockey.elo.elotracker.user.exception

import org.springframework.http.HttpStatus
import org.springframework.web.bind.annotation.ResponseStatus

@ResponseStatus(HttpStatus.NOT_FOUND)
open class UserNotFoundException(message: String?) : Throwable(message)