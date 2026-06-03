vim.g.mapleader = " "
vim.o.cmdheight = 0
vim.o.ignorecase = true
vim.o.laststatus = 3
vim.o.list = true
vim.o.number = true
vim.o.relativenumber = true
vim.o.shiftwidth = 2
vim.keymap.set("n", "<C-s>", vim.cmd.update)
vim.keymap.set("n", "<leader>q", vim.cmd.quit)
vim.keymap.set("n", "<leader>h", vim.cmd.nohlsearch)
vim.keymap.set({ "n", "v" }, "<leader>y", '"+y')
vim.keymap.set({ "n", "v" }, "<leader>p", '"+p')
vim.api.nvim_create_autocmd("TextYankPost", { callback = function() vim.highlight.on_yank() end })

vim.pack.add({
  { src = "https://github.com/catppuccin/nvim" },
  { src = "https://github.com/nvim-mini/mini.nvim" },
  { src = "https://github.com/folke/flash.nvim" },
  { src = "https://github.com/akinsho/toggleterm.nvim" },
  { src = "https://github.com/saghen/blink.cmp", version = "v1" },
  { src = "https://github.com/neovim/nvim-lspconfig" },
})

-- catppuccin/nvim
vim.cmd.colorscheme("catppuccin")

-- nvim-mini/mini.nvim
require("mini.ai").setup()
require("mini.diff").setup()
require("mini.files").setup({ windows = { preview = true } })
require("mini.icons").setup()
require("mini.move").setup()
require("mini.pairs").setup()
require("mini.pick").setup()
require("mini.statusline").setup()
vim.keymap.set("n", "<leader>e", MiniFiles.open)
vim.keymap.set("n", "<leader>f", MiniPick.builtin.files)
vim.keymap.set("n", "<leader>b", MiniPick.builtin.buffers)
vim.keymap.set("n", "<leader>s", MiniPick.builtin.grep_live)

-- folke/flash.nvim
require("flash").setup()
vim.keymap.set({ "n", "x", "o" }, "s", function() require("flash").jump() end)

-- akinsho/toggleterm.nvim
require("toggleterm").setup({ open_mapping = "<C-/>" })
local Terminal = require("toggleterm.terminal").Terminal
local lazygit = Terminal:new({ cmd = "lazygit", direction = "float" })
vim.keymap.set("n", "<leader>g", function() lazygit:toggle() end)

-- saghen/blink.cmp
require("blink.cmp").setup({ keymap = { preset = "enter" } })

-- neovim/nvim-lspconfig
vim.lsp.inlay_hint.enable(true)
vim.lsp.enable({ "clangd" })
vim.diagnostic.config({ virtual_text = true })

vim.api.nvim_create_autocmd("BufWritePre", {
  pattern = "*.cpp",
  callback = function()
    vim.lsp.buf.format()
  end,
})

vim.keymap.set("n", "gd", vim.lsp.buf.definition)
vim.keymap.set("n", "gD", vim.lsp.buf.declaration)
vim.keymap.set("n", "gi", vim.lsp.buf.implementation)
vim.keymap.set("n", "gr", vim.lsp.buf.references)
vim.keymap.set("n", "<leader>rn", vim.lsp.buf.rename)
vim.keymap.set("n", "<leader>ca", vim.lsp.buf.code_action)
