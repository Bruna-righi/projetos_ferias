const express = require('express')
const logger = require('./logger')

const app = express()

logger('ola mundo')

app.get('/main', function (req, res) {
  res.send('Isso aqui eh um caso teste')
})


app.get('/', function (req, res) {
    res.send('Home')
})

app.listen(3000)