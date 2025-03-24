// // updated front end
// "use client"

// import { useState } from "react"
// import "./App.css"
// import CppComponent from "./CppComponent"
// import jsonData from "./backend/out.json"

// function App() {
//   const count = Object.keys(jsonData).length
//   const [current, setCurrent] = useState(0)
//   const [reglist, setReg] = useState([])
//   const [memlist, setMem] = useState([])

//   const nextClick = () => {
//     setReg([])
//     setMem([])
//     if (current < count - 1) {
//       setCurrent(current + 1)
//     }
//   }

//   const prevClick = () => {
//     setReg([])
//     setMem([])
//     if (current > 0) {
//       setCurrent(current - 1)
//     }
//   }

//   const reset = () => {
//     setReg([])
//     setMem([])
//     setCurrent(0)
//   }

//   const run = () => {
//     setReg([])
//     setMem([])
//     setCurrent(count - 1)
//   }

//   // Generate register display with improved styling
//   for (let j = 0; j < 32; j += 2) {
//     reglist.push(
//       <div key={`reg-row-${j}`} className="flex flex-wrap mb-3">
//         <div className="w-full md:w-1/2 px-3">
//           <label className="block text-xs font-semibold text-blue-700 mb-1">X{j}</label>
//           <div className="appearance-none block w-full bg-white text-black border border-blue-200 rounded py-2 px-3 mb-2 leading-tight">
//             {jsonData[current].Reg[j]}
//           </div>
//         </div>
//         <div className="w-full md:w-1/2 px-3">
//           <label className="block text-xs font-semibold text-blue-700 mb-1">X{j + 1}</label>
//           <div className="appearance-none block w-full bg-white text-black border border-blue-200 rounded py-2 px-3 mb-2 leading-tight">
//             {jsonData[current].Reg[j + 1]}
//           </div>
//         </div>
//       </div>,
//     )
//   }

//   // Generate memory display with improved styling
//   for (const x in jsonData[current].Data) {
//     memlist.push(
//       <div key={`mem-${x}`} className="mb-2">
//         <div className="text-xs font-semibold text-blue-700 mb-1">{x}</div>
//         <div className="flex flex-wrap mb-2">
//           <div className="appearance-none w-1/4 bg-white text-black border border-blue-200 rounded py-2 px-3 mx-1">
//             {jsonData[current].Data[x][0]}
//           </div>
//           <div className="appearance-none w-1/4 bg-white text-black border border-blue-200 rounded py-2 px-3 mx-1">
//             {jsonData[current].Data[x][1]}
//           </div>
//           <div className="appearance-none w-1/4 bg-white text-black border border-blue-200 rounded py-2 px-3 mx-1">
//             {jsonData[current].Data[x][2]}
//           </div>
//           <div className="appearance-none w-1/4 bg-white text-black border border-blue-200 rounded py-2 px-3 mx-1">
//             {jsonData[current].Data[x][3]}
//           </div>
//         </div>
//       </div>,
//     )
//   }

//   return (
//     <>
//       <div className="App bg-blue-50 min-h-screen">
//         <div className="container mx-auto p-4">
//           <div className="bg-white rounded-lg shadow-lg border border-blue-200 p-4 mb-6">
//             <CppComponent />

//             {/* Enhanced buttons */}
//             <div className="flex justify-center space-x-3 my-4">
//               <button
//                 onClick={run}
//                 className="bg-blue-600 hover:bg-blue-700 text-white font-medium py-2 px-4 rounded transition-colors duration-200"
//               >
//                 Run
//               </button>
//               <button
//                 onClick={nextClick}
//                 className="bg-blue-600 hover:bg-blue-700 text-white font-medium py-2 px-4 rounded transition-colors duration-200"
//               >
//                 Next
//               </button>
//               <button
//                 onClick={prevClick}
//                 className="bg-blue-600 hover:bg-blue-700 text-white font-medium py-2 px-4 rounded transition-colors duration-200"
//               >
//                 Prev
//               </button>
//               <button
//                 onClick={reset}
//                 className="bg-blue-600 hover:bg-blue-700 text-white font-medium py-2 px-4 rounded transition-colors duration-200"
//               >
//                 Reset
//               </button>
//             </div>

//             <div className="text-center text-sm text-blue-600 mb-4">
//               Step {current + 1} of {count}
//             </div>

//             <div className="flex flex-col md:flex-row">
//               {/* Registers section with card styling */}
//               <div className="w-full md:w-1/2 p-2">
//                 <div className="border border-blue-200 rounded-lg overflow-hidden">
//                   <div className="bg-blue-600 text-white py-2 px-4 font-medium">Registers</div>
//                   <div className="p-4 bg-blue-50">{reglist}</div>
//                 </div>
//               </div>

//               {/* PC, Instruction, and Memory section */}
//               <div className="w-full md:w-1/2 p-2">
//                 <div className="border border-blue-200 rounded-lg overflow-hidden mb-4">
//                   <div className="bg-blue-600 text-white py-2 px-4 font-medium">Program Counter</div>
//                   <div className="p-4 bg-white">
//                     <div className="font-mono">{jsonData[current].PC}</div>
//                   </div>
//                 </div>

//                 <div className="border border-blue-200 rounded-lg overflow-hidden mb-4">
//                   <div className="bg-blue-600 text-white py-2 px-4 font-medium">Instruction</div>
//                   <div className="p-4 bg-white">
//                     <div className="font-mono">{jsonData[current].Message}</div>
//                   </div>
//                 </div>

//                 <div className="border border-blue-200 rounded-lg overflow-hidden">
//                   <div className="bg-blue-600 text-white py-2 px-4 font-medium">Memory</div>
//                   <div className="p-4 bg-blue-50">{memlist}</div>
//                 </div>
//               </div>
//             </div>
//           </div>
//         </div>
//       </div>
//     </>
//   )
// }

// export default App
"use client"

import { useState } from "react"
import "./App.css"
import CppComponent from "./CppComponent"
import jsonData from "./backend/out.json"

function App() {
  const count = Object.keys(jsonData).length
  const [current, setCurrent] = useState(0)
  const [reglist, setReg] = useState([])
  const [memlist, setMem] = useState([])

  const nextClick = () => {
    setReg([])
    setMem([])
    if (current < count - 1) {
      setCurrent(current + 1)
    }
  }

  const prevClick = () => {
    setReg([])
    setMem([])
    if (current > 0) {
      setCurrent(current - 1)
    }
  }

  const reset = () => {
    setReg([])
    setMem([])
    setCurrent(0)
  }

  const run = () => {
    setReg([])
    setMem([])
    setCurrent(count - 1)
  }

  // Generate register display with improved styling
  for (let j = 0; j < 32; j += 2) {
    reglist.push(
      <div key={`reg-row-${j}`} className="flex flex-wrap mb-3">
        <div className="w-full md:w-1/2 px-3">
          <label className="block text-xs font-semibold text-blue-700 mb-1">X{j}</label>
          <div className="appearance-none block w-full bg-white text-black border border-blue-200 rounded py-2 px-3 mb-2 leading-tight">
            {jsonData[current].Reg[j]}
          </div>
        </div>
        <div className="w-full md:w-1/2 px-3">
          <label className="block text-xs font-semibold text-blue-700 mb-1">X{j + 1}</label>
          <div className="appearance-none block w-full bg-white text-black border border-blue-200 rounded py-2 px-3 mb-2 leading-tight">
            {jsonData[current].Reg[j + 1]}
          </div>
        </div>
      </div>,
    )
  }

  // Generate memory display with improved styling
  for (const x in jsonData[current].Data) {
    memlist.push(
      <div key={`mem-${x}`} className="mb-2">
        <div className="text-xs font-semibold text-blue-700 mb-1">{x}</div>
        <div className="flex flex-wrap mb-2">
          <div className="appearance-none w-1/4 bg-white text-black border border-blue-200 rounded py-2 px-3 mx-1">
            {jsonData[current].Data[x][0]}
          </div>
          <div className="appearance-none w-1/4 bg-white text-black border border-blue-200 rounded py-2 px-3 mx-1">
            {jsonData[current].Data[x][1]}
          </div>
          <div className="appearance-none w-1/4 bg-white text-black border border-blue-200 rounded py-2 px-3 mx-1">
            {jsonData[current].Data[x][2]}
          </div>
          <div className="appearance-none w-1/4 bg-white text-black border border-blue-200 rounded py-2 px-3 mx-1">
            {jsonData[current].Data[x][3]}
          </div>
        </div>
      </div>,
    )
  }

  return (
    <>
      <div className="App bg-blue-50 min-h-screen">
        <header className="bg-blue-700 text-white text-center text-2xl font-bold py-4 shadow-md">
          RISC-V Simulator
        </header>
        <div className="container mx-auto p-4">
          <div className="bg-white rounded-lg shadow-lg border border-blue-200 p-4 mb-6">
            <CppComponent />

            {/* Enhanced buttons */}
            <div className="flex justify-center space-x-3 my-4">
              <button onClick={run} className="bg-blue-600 hover:bg-blue-700 text-white font-medium py-2 px-4 rounded transition-colors duration-200">
                Run
              </button>
              <button onClick={nextClick} className="bg-blue-600 hover:bg-blue-700 text-white font-medium py-2 px-4 rounded transition-colors duration-200">
                Next
              </button>
              <button onClick={prevClick} className="bg-blue-600 hover:bg-blue-700 text-white font-medium py-2 px-4 rounded transition-colors duration-200">
                Prev
              </button>
              <button onClick={reset} className="bg-blue-600 hover:bg-blue-700 text-white font-medium py-2 px-4 rounded transition-colors duration-200">
                Reset
              </button>
            </div>

            <div className="text-center text-sm text-blue-600 mb-4">
              Step {current + 1} of {count}
            </div>

            <div className="flex flex-col md:flex-row">
              {/* Registers section with card styling */}
              <div className="w-full md:w-1/2 p-2">
                <div className="border border-blue-200 rounded-lg overflow-hidden">
                  <div className="bg-blue-600 text-white py-2 px-4 font-medium">Registers</div>
                  <div className="p-4 bg-blue-50">{reglist}</div>
                </div>
              </div>

              {/* PC, Instruction, and Memory section */}
              <div className="w-full md:w-1/2 p-2">
                <div className="border border-blue-200 rounded-lg overflow-hidden mb-4">
                  <div className="bg-blue-600 text-white py-2 px-4 font-medium">Program Counter</div>
                  <div className="p-4 bg-white">
                    <div className="font-mono">{jsonData[current].PC}</div>
                  </div>
                </div>

                <div className="border border-blue-200 rounded-lg overflow-hidden mb-4">
                  <div className="bg-blue-600 text-white py-2 px-4 font-medium">Instruction</div>
                  <div className="p-4 bg-white">
                    <div className="font-mono">{jsonData[current].Message}</div>
                  </div>
                </div>

                <div className="border border-blue-200 rounded-lg overflow-hidden">
                  <div className="bg-blue-600 text-white py-2 px-4 font-medium">Memory</div>
                  <div className="p-4 bg-blue-50">{memlist}</div>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
    </>
  )
}

export default App
