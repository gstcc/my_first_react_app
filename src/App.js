import React, { useState } from "react";
import { useEffect } from "react";

import './App.css'
import SearchIcon from './search.svg';
import MovieCard from "./MovieCard";    

const API_URL = 'http://www.omdbapi.com?apikey=311aa7c3'

const App = () => {

    const [movies, setMovies] = useState([])
    const [searcTerm, setSearchTerm] = useState('')

    const searchMovies = async (title) => {
        const response = await fetch(`${API_URL}&s=${title}`);
        const data = await response.json();

        console.log(data)

        setMovies(data.Search);
    }

    useEffect(() => {
        searchMovies('');
    }, []);

    return (
        <div className="app">
            <h1>MovieLand</h1>

            <div className="search">
                <input
                    placeholder="Search for movies"
                    value = {searcTerm}
                    onChange={(e) => setSearchTerm(e.target.value)}
                    onKeyUp={(e) => e.key === 'Enter' ? searchMovies(searcTerm) : null}
                />
                <img 
                    src={SearchIcon} 
                    alt="search"
                    onClick={() => searchMovies(searcTerm)}
                />
            </div>

            {movies?.length > 0 ? 
                    ( <div className="container">
                        {movies.map((movie) => (
                            <MovieCard movie={movie}/>
                        ))}
                    </div> 
                    ) : (
                     <div className="empty"> 
                        <h2>No Movies Found</h2>
                    </div> 
            )};
           
        </div>
    )
}

export default App;