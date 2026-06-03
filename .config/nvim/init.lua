vim.g.mapleader = " "
vim.opt.cmdheight = 0
vim.opt.laststatus = 3
vim.opt.shiftwidth = 2
vim.opt.list = true
vim.opt.number = true
vim.opt.relativenumber = true
vim.opt.ignorecase = true
vim.opt.smartcase = true
vim.keymap.set("n", "<C-s>", vim.cmd.update)
vim.keymap.set("n", "<leader>q", vim.cmd.quit)
vim.keymap.set("n", "<leader>h", vim.cmd.nohlsearch)
vim.keymap.set({ "n", "v" }, "<leader>y", '"+y')
vim.keymap.set({ "n", "v" }, "<leader>p", '"+p')
vim.api.nvim_create_autocmd("TextYankPost", { callback = function() vim.highlight.on_yank() end })

-- catppuccin/nvim
vim.pack.add({ { src = "https://github.com/catppuccin/nvim" } })
vim.cmd.colorscheme("catppuccin")

-- nvim-mini/mini.nvim
vim.pack.add({ { src = "https://github.com/nvim-mini/mini.nvim" } })
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
vim.pack.add({ { src = "https://github.com/folke/flash.nvim" } })
require("flash").setup()
vim.keymap.set("n", "s", function() require("flash").jump() end)

-- akinsho/toggleterm.nvim
vim.pack.add({ { src = "https://github.com/akinsho/toggleterm.nvim" } })
require("toggleterm").setup({ open_mapping = "<C-/>" })
local Terminal = require("toggleterm.terminal").Terminal
local lazygit = Terminal:new({ cmd = "lazygit", direction = "float" })
vim.keymap.set("n", "<leader>g", function() lazygit:toggle() end)

-- saghen/blink.cmp
vim.pack.add({ { src = "https://github.com/saghen/blink.cmp", version = "v1" } })
require("blink.cmp").setup({ keymap = { preset = "enter" } })

-- neovim/nvim-lspconfig
vim.pack.add({ { src = "https://github.com/neovim/nvim-lspconfig" } })
vim.lsp.enable({ "clangd" })
vim.lsp.inlay_hint.enable(true)
vim.diagnostic.config({ virtual_lines = { current_line = true } })
vim.keymap.set("n", "gd", vim.lsp.buf.definition)
vim.keymap.set("n", "gr", vim.lsp.buf.references)
vim.keymap.set("n", "<leader>rn", vim.lsp.buf.rename)
vim.keymap.set("n", "<leader>ca", vim.lsp.buf.code_action)
vim.api.nvim_create_autocmd("BufWritePre", { callback = function() vim.lsp.buf.format() end })
